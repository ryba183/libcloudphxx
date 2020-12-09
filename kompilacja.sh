cd build
rm -rf *
cmake ..  -DCMAKE_INSTALL_PREFIX=/mnt/local/pzmij/UWLCM_singu/singularity/local_folder -DCMAKE_BUILD_TYPE=Debug
make -j 20
make install -j20
