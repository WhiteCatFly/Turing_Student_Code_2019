## Description

A simple web crawler.

By default, the target website is http://info.ruc.edu.cn and the crawled webs will be saved in the directory 'pages/'.

The homepage and output directory can be changed using the command line arguments '-h' and '-o', respectively.

The number of crawled webs and time used will be written to 'crawler-log' and the sorted urls crawled will be written to 'list.txt'.

For http://info.ruc.edu.cn, a total number of 6600+ webs can be crawled in less than 20 minutes.

## Usage

```shell
make
./prog (-h homepage_url) (-o output_directory)
make clean
```

