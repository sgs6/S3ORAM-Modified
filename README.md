# S3ORAM-Modified

Notice: The following config requires the stack limit to be increased. To confirm it works, the command `ulimit -s unlimited` was performed in the terminal to remove the soft limit.

Current max config as follows:

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

config.h: 


#define BLOCK_SIZE 40

#define HEIGHT 12

#define BUCKET_SIZE 248

#define EVICT_RATE 124

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

results in:


[S3ORAM] There are 4094 non-leaf nodes, which is 1015312 rows of data.

[S3ORAM] There are 4095 leaf nodes, which is 1015560 rows of data.

[S3ORAM] Combined, there are 8191 nodes, which is 2031368 rows of data.

Last data set: 458149, 1015716, 235137, 5160, 3

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Dependencies:

ntl==9.10.0

libboost-all-dev==any

ZeroMQ

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
