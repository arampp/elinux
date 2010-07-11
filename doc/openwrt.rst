Bauen
=====

Problem: m4 fehlt beim bauen von bison
--------------------------------------
Lösung:
rm staging_dir/host/bin/m4
ln -s /usr/bin/m4 staging_dir/host/bin/m4
make V=99
