use strict;
use warnings;

open(my $fh, '>', 'report.txt');
open (my $file, '<', 'fft.mtrace') or die $!;

while (my $firstLine = <$file>)  {
    if ($firstLine =~ /MemWrite ([a-zA-Z0-9]*)\:.*/) {
	my @fieldsfirstline = split /:/, $firstLine;	
	last; 
    }
}


while (my $line = <$file>)  {
    if ($line =~ /MemWrite ([a-zA-Z0-9]*)\:.*/) {
	my @fields = split /:/, $line;
	my $oneName = substr($fields[1], 11, 2);
	my $cycletemp = int(($fields[0] - $fieldsfirstline[0])/"1000");
	my $cycle = "10000" + $cycletemp*"0.2";
	my $string = $cycle ." ". $oneName . $fields[5];
        print $fh "$string\n";
    }
    if ($line =~ /MemRead ([a-zA-Z0-9]*)\:.*/) {
	my @fields = split /:/, $line;
	my $oneName = substr($fields[1], 11, 2);
	my $cycletemp = int(($fields[0] - $fieldsfirstline[0])/"1000");
	my $cycle = "10000" + $cycletemp*"0.2";
	my $string = $cycle ." ". $oneName . $fields[5];
        print $fh "$string\n";
    }
}
close $file;

close $fh;
print "done\n";
