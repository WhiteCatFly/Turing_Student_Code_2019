#! /usr/bin/env python3

import sys

import jieba
import jieba.posseg as pseg

from typing import List, Mapping, Tuple, Callable, Iterable

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


class Document:
    id: int
    weight: float

    __slots__ = ["id", "weight"]

    def __init__(self, id: int, weight: float = 1.0):
        self.id = id
        self.weight = weight


def split_list(func: Callable, lst: Iterable) -> List:
    if len(lst) == 0:
        return []
    ret = []
    now = []
    for item in lst:
        if func(item):
            if now != []:
                ret.append(now)
            now = []
        else:
            now.append(item)
    if now != []:
        ret.append(now)
    return ret


# def find_word(word: str, data: Database) -> Mapping[int, float]:
#     if word not in data.word_list:
#         return {}
#     ret = {}
#     sum = 0
#     num = {}
#     wordobj = data.word_list[word]
#     wordobj.


if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print("Usage: %s database pattern" % sys.argv[0], file=sys.stderr)
        exit(1)

    with open(sys.argv[1], "rb") as fdatain:
        database: Database = pickle.load(fdatain)

    docs = []
    for doc in database.file_list:
        docs.append(Document(doc[1]))

    words = pseg.cut(sys.argv[2])
    sentenses = split_list(lambda word: word.flag != 'x', words)

    for sentense in sentenses:
        pass
