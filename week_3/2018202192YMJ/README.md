## Description

A simple web crawler.

By default, the target website is http://econ.ruc.edu.cn and the crawled webs will be saved in the directory 'econ/', and the report period is 10 webs per report(to report the number of webs allready crawled and in queue and time used during the crawling process).

The homepage, output directory and report period can be changed using the command line arguments '-h', '-o' and '-p', respectively. In particular, the report can be disabled using '-p 0'.

The number of crawled webs and time used will be written to 'crawler-log', the sorted urls crawled will be written to 'url_list.txt' and the trace of the bfs will be written to 'trace.txt'.

For http://info.ruc.edu.cn, a total number of 6746 webs can be crawled.

For http://econ.ruc.edu.cn, a total number of 7430 webs can be crawled.

## Usage

```shell
make
./prog (-h homepage_url) (-o output_directory) (-p report_period)
make clean
```

