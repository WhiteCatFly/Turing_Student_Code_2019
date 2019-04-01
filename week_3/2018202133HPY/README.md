
# Simple Crawler

## Usage

```
$ make
$
$ # Do some configure
$ vi config.ini
$
$ ./main
```

## Configure

This program will read `config.ini` in the working directory

### Section `Global`

`root` : The root url to crawl.

`savePath` : The root directory to save the web page.

### Section `EventLoop`

`workers` : The number of working threads.

### Section `MultiHandle`

`handles` : The number of requests make at the same time in one thread.

### Section `EasyHandle`

`timeout` : Timeout ( in milliseconds ) for one request.
