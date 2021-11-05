#! /bin/bash -e
export DESTDIR=build-temp
rm -rf $DESTDIR
mkdir $DESTDIR

# create dockcross script
echo "Generating dockercross script"
IMG=tvoneicken/sensorgnome-dockcross:armv7-rpi-buster-main
docker run $IMG >sensorgnome-dockcross
chmod +x sensorgnome-dockcross

echo "Cross-compiling and installing"
./sensorgnome-dockcross -i $IMG \
    make clean install DESTDIR=$DESTDIR STRIP=armv7-unknown-linux-gnueabi-strip

cp -r DEBIAN $DESTDIR
mkdir -p packages
dpkg-deb -v --build $DESTDIR packages/fcd.deb
# dpkg-deb --contents packages/sg-control.deb
ls -lh packages/fcd.deb
