# S3ORAM-Modified

Notice: The following config requires the stack limit to be increased. To confirm it works, the command `ulimit -s unlimited` was performed in the terminal to remove the soft limit.

Notice, this amount of data, 3 sets 5 million rows of 5 columns and 1 set of 5 million rows and 2 columns requires 11 GB of memory.

Current high end config as follows:

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

config.h: 


#define BLOCK_SIZE 40

#define HEIGHT 9

#define BUCKET_SIZE 4888

#define EVICT_RATE 2444

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

results in:

[S3ORAM] There are 510 non-leaf nodes, which is 2492880 rows of data.

[S3ORAM] There are 511 leaf nodes, which is 2497768 rows of data.

[S3ORAM] Combined, there are 1023 nodes, which is 5000424 rows of data.

Last data set: 2989959, 4999235, 350067, 102, 5

And data key 4999235 can be confirmed to be at the 5000424th row of data via `cat allData.csv | grep -n "4999235,350067,102,5"`

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Dependencies:

ntl==9.10.0

libboost-all-dev==any

ZeroMQ

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
