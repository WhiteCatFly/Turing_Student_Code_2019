## Description

A simple web crawler.

By default, the target website is http://econ.ruc.edu.cn and the crawled webs will be saved in the directory 'econ/', and the report interval is 10 webs (report the number of webs already crawled and in queue and time used during the crawling process every 10 webs). Also, the program will backup the information according to the backup interval, which is 100 webs by default.

The homepage, output directory, report interval and backup interval can be changed using the command line arguments '-h', '-o', '-p' and '-b', respectively. In particular, the report can be disabled using '-p 0'.

In addition, in case the crawler is terminated unexpectedly, you can use ```'./prog -c'``` next time to retieve the information and continue to crawl from where it stopped last time. You can also use ```'./prog -r'``` to continue crawling after retrying to crawl the urls failed to be crawled last time.

The number of crawled webs and time used will be written to 'crawler-log', and the sorted urls crawled will be written to 'url_list.log'. Unsuccesfully crawled urls will be written to 'failed_urls.log'.

For http://info.ruc.edu.cn, a total number of 6746 webs can be crawled.

For http://econ.ruc.edu.cn, a total number of 7430 webs can be crawled.

## Usage

```shell
make
./prog (-h homepage_url) (-o output_directory) (-p report_interval) (-b backup_interval) (-c) (-r)
make clean
```

