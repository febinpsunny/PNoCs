use strict;
use warnings;
open INFILE, '<blackscholes.trace';
open OUTFILE, '>blackscholest.trace';
<INFILE>; #discards first line
print OUTFILE $_ while (<INFILE>);
close OUTFILE;
close INFILE;

open INFILE, '<blackscholest.trace';
open OUTFILE, '>blackscholes.trace';
<INFILE>; #discards first line
print OUTFILE $_ while (<INFILE>);
close OUTFILE;
close INFILE;
 
open(my $fh, '>', 'blackscholes_modified.txt');
open (my $file, '<', 'blackscholes.trace') or die $!;
my $firstLine = <$file>;
my @parsestring = split /:/, $firstLine;
my $previousvalue = "0"; 
while (my $line = <$file>)  {
    if ($line =~ /MemWrite ([a-zA-Z0-9]*)\:.*/) {
	my @fields = split /:/, $line;
	my $oneName = substr($fields[1], 11, 2);
	my $cycletemp = int(($fields[0] - $parsestring[0])/"1000");
	my $cycle = "10000" + $cycletemp*"0.2";
	if($cycle >= $previousvalue)
	{
	 my $string = $cycle ." ". $oneName . $fields[5];
         print $fh "$string\n";
	$previousvalue = $cycle;
        }
    }
    if ($line =~ /MemRead ([a-zA-Z0-9]*)\:.*/) {
	my @fields = split /:/, $line;
	my $oneName = substr($fields[1], 11, 2);
	my $cycletemp = int(($fields[0] - $parsestring[0])/"1000");
	my $cycle = "10000" + $cycletemp*"0.2";
	if($cycle >= $previousvalue)
	{
	 my $string = $cycle ." ". $oneName . $fields[5];
         print $fh "$string\n";
	$previousvalue = $cycle;
        }
    }
}
close $file;

close $fh;
print "done\n";
