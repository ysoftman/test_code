#!/bin/bash

set -x
echo "apple\nlemon"

# disable interpretation escape
echo -E "apple\nlemon"

# interpretation escape
# https://www.gnu.org/software/coreutils/manual/html_node/echo-invocation.html
# \a alert (bell)
# \b backspace
# \c produce no further output
# \e escape
# \f form feed
# \n newline
# \r carriage return
# \t horizontal tab
# \v vertical tab
# \\ backslash
echo -e "apple\nlemon"

# without trailing newline
echo -n "apple\nlemon"

