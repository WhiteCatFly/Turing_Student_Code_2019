import hashlib
import json
import math
import os
import zlib

import bs4
import jieba
from tqdm import tqdm

def is_chinese_char(ch):
    chv = ord(ch)
    if 0x4e00 <= chv <= 0x9fa5:
        return True
    return False

def html_to_text(page):
    soup = bs4.BeautifulSoup(page, 'html5lib')
    return soup.get_text()

class ArticlePage:
    def __init__(self, index, data, from_json=None):
        if from_json is not None:
            obj = from_json
            self.index = obj['index']
            self.data_src = None
            self.data_text = None
            self.data_zh = None
            self.keywords = obj['keywords']
        else:
            self.index = index # id
            self.data_src = data # initial data
            self.data_text = html_to_text(self.data_src)
            self.data_zh = ''.join(i if is_chinese_char(i) else '' for i in self.data_text)
            self.keywords = list(jieba.cut_for_search(self.data_zh))
        # tf
        self.word_cnt = {}
        for word in self.keywords:
            if word not in self.word_cnt:
                self.word_cnt[word] = 0
            self.word_cnt[word] += 1
        self.tf = {}
        for word in self.keywords:
            self.tf[word] = self.word_cnt[word] / len(self.keywords)
        # prepare for tfidf
        self.tfidf = {}
        del self.data_src
        del self.data_text
        del self.data_zh
        del self.word_cnt
        return
    def export_to_json(self):
        obj = {
            'index': self.index,
            'keywords': self.keywords,
        }
        return json.dumps(obj, indent=4)
    def clean(self):
        del self.keywords
        return
    def show(self, entries=30):
        keywords = []
        for word in self.tfidf:
            keywords.append((self.tfidf.get(word, 0), word))
        keywords.sort(reverse=True)
        print([i[1] for i in keywords[:entries]])
    pass

class ArticleLibrary:
    def __init__(self):
        self.articles = set()
        self.articles_index = {}
        self.word_pages = {}
        self.idf = {}
        return
    def add_article(self, data):
        self.articles.add(data)
        self.articles_index[data.index] = data
        return
    def build_idf(self):
        self.word_pages = {}
        for article in self.articles:
            for word in article.tf:
                if word not in self.word_pages:
                    self.word_pages[word] = 0
                self.word_pages[word] += 1
        self.idf = {}
        for word in self.word_pages:
            self.idf[word] = math.log(len(self.articles) / (1 + self.word_pages[word]), 10)
        # tfidf
        for article in self.articles:
            for word in article.tf:
                article.tfidf[word] = article.tf[word] * self.idf[word]
            del article.tf
        del self.idf
        del self.word_pages
        return
    def query(self, keywords, entries=1):
        if not isinstance(keywords, list):
            keywords = jieba.cut_for_search(keywords)
        keywords = set(keywords)
        print(keywords)
        results = []
        for article in self.articles:
            weights = []
            for word in keywords:
                weights.append(article.tfidf.get(word, 0))
            weights.sort(reverse=True)
            score = sum(weights[i] * 0.95**i for i in range(0, len(weights)))
            results.append((score, article.index))
        results.sort(reverse=True)
        return [{'index': i[1], 'relevance': i[0]} for i in results[:entries]]
    pass

def get_library_files():
    files = []
    for i, j, k in os.walk('./download/'):
        for f in k:
            path = (i + '/' + f).replace('\\', '/').replace('//', '/')
            files.append(path)
    return files

def del_database():
    for i, j, k in os.walk('./database/'):
        for f in k:
            path = (i + '/' + f).replace('\\', '/').replace('//', '/')
            os.remove(path)

def refresh_database():
    del_database()
    files = get_library_files()
    for fn in tqdm(files):
        # index
        findex = fn[11:]
        hash_val = hashlib.sha256(findex.encode('utf-8')).hexdigest()[:16]
        fname = './database/%s.json.gz' % hash_val
        if os.path.exists(fname):
            continue
        # read from file
        fhandle = open(fn, 'rb')
        content = fhandle.read()
        fhandle.close()
        content = content.decode('utf-8', 'ignore')
        # make page
        ap = ArticlePage(findex, content)
        jdata = ap.export_to_json()
        ap.clean()
        jbin = zlib.compress(jdata.encode('utf-8'), level=9)
        # write
        fhandle = open(fname, 'wb')
        fhandle.write(jbin)
        fhandle.close()
    return 

def load_from_database(lib):
    files = list(os.listdir('./database/'))
    for fname in tqdm(files):
        # read from file
        fhandle = open('./database/%s' % fname, 'rb')
        jbin = fhandle.read()
        fhandle.close()
        jdata = zlib.decompress(jbin).decode('utf-8')
        jobj = json.loads(jdata)
        # save
        page = ArticlePage('', '', from_json=jobj)
        page.clean()
        lib.add_article(page)
    return    

lib = ArticleLibrary()

rs = input('Do you want to refresh the database? (y/n) ')
if rs in ['y', 'Y', 'Yes', 'yes', 'YES']:
    refresh_database()

print('Loading database... ', end='')
load_from_database(lib)
print('Done.')

print('Building idf... ', end='')
lib.build_idf()
print('Done.')

while True:
    qs = input('>>> ')
    if qs in ['q', 'Q', 'quit', 'Quit', 'QUIT']:
        break
    qres = lib.query(qs, entries=2)
    for result in qres:
        index = result['index']
        relevance = result['relevance']
        print('[Relevance: %.8f]' % relevance)
        lib.articles_index[index].show()

        fname = './download/' + index
        fhandle = open(fname, 'rb')
        cbin = fhandle.read()
        content = cbin.decode('utf-8', 'ignore')
        fhandle.close()
        zh_cont = ''.join(i if is_chinese_char(i) else
                          '' for i in html_to_text(content))
        print('%s...\n' % zh_cont[:100])
    pass
