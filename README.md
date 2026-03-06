# ZeroMQToEICrecon

==== How to run ====
```
run ./eic-shell
source /opt/detector/epic-main/bin/thisepic.sh
cd ZeroMQTest/
export EICrecon_MY=${PWD}/EICrecon_MY
export CPATH="/opt/local/include/EICrecon:$CPATH"
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$EIC_SHELL_PREFIX -DCMAKE_INSTALL_PREFIX="$EICrecon_MY"
make install -j8

eicrecon -Pplugins=ZmqSourcePlugin tcp://localhost:5555 -Pdd4hep:xml_files=epic_craterlake_tracking_only.xml -Ppodio:output_collections="KumaTOFBarrelClusterHits"

```
