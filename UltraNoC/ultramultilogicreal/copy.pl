use strict;
use warnings;
open(my $fh, '>', 'bodytrack_modified_1.txt');
open (my $file, '<', 'bodytrack_modified.txt') or die $!;
my $count = 0;
while (my $line = <$file>)  {
    if($count <= 1000000)
 {
    print $fh "$line";
    $count = $count +1;
}
    
}
close $file;

close $fh;
print "done\n";
