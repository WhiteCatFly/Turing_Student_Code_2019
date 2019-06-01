#! /usr/bin/env python3

import sys

import jieba
import jieba.posseg as pseg

from functools import reduce
from typing import List, Mapping, Tuple

try:
    pickle = __import__("cPickle")
except ImportError:
    import pickle


class Word:
    id: int
    name: str

    # Mapping[doc, List[pos, linum]]
    pos: Mapping[int, List[Tuple[int, int]]]
    __slots__ = ["id", "pos", "name"]

    def __init__(self, id: int, name: str):
        self.id = id
        self.name = name
        self.pos = {}

    def add(self, doc_id: int, pos: int, line_num: int):
        if doc_id not in self.pos:
            self.pos[doc_id] = []
        self.pos[doc_id].append((pos, line_num))


class Database:
    _fileno: int
    _wordno: int
    file_list: Mapping[str, int]
    word_list: Mapping[str, Word]
    __slots__ = ["file_list", "word_list", "_fileno", "_wordno"]

    def __init__(self):
        self._fileno = 0
        self._wordno = 0
        self.file_list = {}
        self.word_list = {}

    def add(self, word: str, doc_name: str, pos: int, line_num: int):
        if word not in self.word_list:
            self.word_list[word] = Word(self._wordno, word)
            self._wordno += 1
        word_obj = self.word_list[word]

        if doc_name not in self.file_list:
            self.file_list[doc_name] = self._fileno
            self._fileno += 1
        docno = self.file_list[doc_name]

        word_obj.add(docno, pos, line_num)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: %s filelist output" % sys.argv[0], file=sys.stderr)
        exit(1)

    database = Database()

    cnt = 1
    with open(sys.argv[1]) as sfilelist:
        for filename in sfilelist:
            filename = filename.strip()
            if filename == '':
                continue
            try:
                with open(filename) as inputstream:
                    linenum = 1
                    for line in inputstream:
                        wordcnt = 1
                        words = pseg.cut(line)
                        words = list(filter(lambda x: x.flag != 'x', words))
                        for word, flag in words:
                            database.add(word, filename, wordcnt, linenum)
                            wordcnt += 1

                        wordcnt = 1
                        for word0, word1 in zip(words[:-1], words[1:]):
                            word = word0.word + word1.word
                            database.add(word, filename, wordcnt, linenum)
                            wordcnt += 1
                        linenum += 1
                print(cnt, filename)
                cnt += 1
            except FileNotFoundError:
                print(filename, "not fount")

    # with open(sys.argv[2], "wb") as fout:
    #     pickle.dump(database, fout)
