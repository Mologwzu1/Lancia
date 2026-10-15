cd /apollo_workspace/output/logs/
rm -f *.log
for i in {0..15}
do
    rm -f ${i}/*
done

cd /apollo_workspace/output/tmp/
rm -rf *
for i in {0..15}
do
    mkdir ${i}
done
mkdir cyber_y

cd cyber_y
mkdir manager_shm monitor_shm writer_shm