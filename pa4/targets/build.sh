if [ "$1" = "clean" ]; then
    rm -f target[0-7] cookie
else
    python3 ./build.py

    sudo chmod 555 target[0-7]
    sudo chown root:$SUDO_USER target[2-7]
    sudo chmod 6777 target[2-7]
    for t in target[2-7]; do
        if [ `stat -c '%a' $t` -ne 6777 ]; then
            echo -e "Setuid permission could not be set. Make sure your files are in a native Linux folder and not a VirtualBox shared folder.\n";
            rm -f target[0-7]
            exit 1;
        fi;
    done
fi
