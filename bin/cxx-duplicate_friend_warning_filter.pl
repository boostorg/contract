# $Id$ #

@buffer = ();
@errors = ();

while (<>) {
    if (/^In file included from/ or /from/ or @buffer > 0) {
        push(@buffer, $_);
        #print "DEBUG: added $_ to buffer\n\n\n";
        if (/warning/ or /error/) {
            #print "DEBUG: clearing buffer because of $_\n\n";
            if (not /already a friend/) {
                print @buffer;
                push(@errors, @buffer);
            }
            @buffer = ();
        }
    } else {
        if (/error/ or (/warning/ and not /already a friend/
                and not /\/usr\/bin\/ld/)) {
            push(@errors, $_);
        }
        print if not /already a friend/ and not /\/usr\/bin\/ld/;
    }
}

if(@errors > 0) {
    #print "***** build did not complete, had the following errors or warnings: *****\n";
    #print @errors;
    exit 1;
}

