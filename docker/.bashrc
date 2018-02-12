export PS1="\u@\h:\w\$ "
export LANG=ko_KR.utf8
export LC_ALL=ko_KR.utf8

alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l.='ls -d .* --color=auto'
alias ll='ls -ahl --color=auto'
alias ls='ls --color=auto'
alias vi='vim'
alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
alias cdaconf='cd /home/ysoftman/httpd/conf'
alias cdalog='cd /home/ysoftman/httpd/logs'
alias taila='tail -F /home/ysoftman/httpd/logs/access_log'
alias taile='tail -F /home/ysoftman/httpd/logs/error_log'
alias astart='sudo /home/ysoftman/httpd/bin/apachectl -k start'
alias astop='sudo /home/ysoftman/httpd/bin/apachectl -k stop'
