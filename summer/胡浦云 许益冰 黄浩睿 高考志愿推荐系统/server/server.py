import json
import math

from aiohttp import web

global g_majorWeights


def getWeight(diff):
    return math.exp(-(diff - 5)**2 / (2 * 10**2))


g_majorWeights = {
    "A+": 4,
    "A": 3.6,
    "A-": 3.3,
    "B+": 3,
    "B": 2.6,
    "B-": 2.3,
    "C+": 2,
    "C": 1.6,
    "C-": 1.3
}

provinceIDs = {
    '北京': 11,
    '天津': 12,
    '河北': 13,
    '山西': 14,
    '内蒙古': 15,
    '辽宁': 21,
    '吉林': 22,
    '黑龙江': 23,
    '上海': 31,
    '江苏': 32,
    '浙江': 33,
    '安徽': 34,
    '福建': 35,
    '江西': 36,
    '山东': 37,
    '河南': 41,
    '湖北': 42,
    '湖南': 43,
    '广东': 44,
    '广西': 45,
    '海南': 46,
    '重庆': 50,
    '四川': 51,
    '贵州': 52,
    '云南': 53,
    '西藏': 54,
    '陕西': 61,
    '甘肃': 62,
    '青海': 63,
    '宁夏': 64,
    '新疆': 65
}


class Server:
    class BadRequest(Exception):
        def __init__(self, *args, **kwargs):
            Exception.__init__(self, *args, **kwargs)

    def __init__(self, infoFileName: str, scoreFileName: str,
                 provinceScoreFileName: str):
        with open(infoFileName, encoding='utf-8') as infofile:
            self.schoolInfo = json.load(infofile)
        with open(scoreFileName, encoding='utf-8') as scorefile:
            scores = json.load(scorefile)
        self.scoreList = {}
        for record in scores:
            pid = record["province"]
            tid = record["type"]
            sid = record["school"]
            score = record["score"]
            rank = record["rank"]

            if pid not in self.scoreList:
                self.scoreList[pid] = {}
            province = self.scoreList[pid]
            if tid not in province:
                province[tid] = {}
            ptype = province[tid]
            if sid not in ptype:
                ptype[sid] = {}
            school = ptype[sid]
            school["id"] = sid
            school["score"] = score
            school["rank"] = rank
        with open(provinceScoreFileName, encoding='utf-8') as pscorefile:
            score2rank = json.load(pscorefile)
        self.rank2score = {}
        for pids in score2rank:
            province = score2rank[pids]
            pid = int(pids)
            if pid not in self.rank2score:
                self.rank2score[pid] = {}
            r2sprovince = self.rank2score[pid]
            for tids in province:
                tid = int(tids)
                ptype = province[tids]
                if tid not in r2sprovince:
                    r2sprovince[tid] = []
                r2sptype = r2sprovince[tid]
                try:
                    for scores in ptype["2019"]:
                        rank = ptype["2019"][scores]
                        score = int(scores)
                        r2sptype.append((rank, score))
                except KeyError:
                    pass
        for pid in self.rank2score:
            for ptype in self.rank2score[pid]:
                self.rank2score[pid][ptype].sort(key=lambda x: x[1],
                                                 reverse=True)
        #print(self.rank2score)

    def onError(self, msg):
        return web.json_response({"code": 1, "msg": msg, "data": []})

    def genSchoolData(self, schoolid, ptype, scores):
        ret = {}
        ret["schoolID"] = schoolid
        ret["type"] = ptype

        score = scores[schoolid]["score"]
        #print(score)

        ret["formerScores"] = [
            score["2014"], score["2015"], score["2016"], score["2017"],
            score["2018"]
        ]
        ret["predictScore"] = score["2019"]

        return ret

    def getScoreByRank(self, rank, province, ptypeid):
        try:
            pr2s = self.rank2score[province]
            ptyper2s = pr2s[ptypeid]
            assert len(ptyper2s) > 0
            for rank1, score1 in ptyper2s:
                if rank1 >= rank:
                    return score1
            return 0
        except Exception:
            return None

    def getListByScore(self, score, province, ptypeid, expectedMajor):
        ret = {"code": 0, "msg": "OK", "data": []}
        score = max(score, 0)
        score = min(score, 750)
        score = int(score)

        schools = [[
            self.scoreList[province][ptypeid][school]["id"],
            getWeight(
                score -
                self.scoreList[province][ptypeid][school]["score"]["2019"]),
            score - self.scoreList[province][ptypeid][school]["score"]["2019"]
        ] for school in self.scoreList[province][ptypeid]]

        for school in schools:
            sid = str(school[0])
            info = self.schoolInfo[sid]
            if info["is985"]:
                school[1] *= 2
            if info["is211"]:
                school[1] *= 2

            if expectedMajor in info["specialWeights"]:
                school[1] *= g_majorWeights[info["specialWeights"]
                                            [expectedMajor]]
        schools.sort(key=lambda x: x[1], reverse=True)

        targets = [[], [], []]  # 冲刺， 稳健， 保底
        for school in schools:
            if school[2] >= 20:
                targets[2].append(school[0])
            elif school[2] >= 10:
                targets[1].append(school[0])
            else:
                targets[0].append(school[0])

        for school in targets[0][:3]:
            ret["data"].append(
                self.genSchoolData(school, "冲刺",
                                   self.scoreList[province][ptypeid]))

        for school in targets[1][:3]:
            ret["data"].append(
                self.genSchoolData(school, "稳健",
                                   self.scoreList[province][ptypeid]))

        for school in targets[2][:3]:
            ret["data"].append(
                self.genSchoolData(school, "保底",
                                   self.scoreList[province][ptypeid]))

        return ret

    async def handle(self, request):
        global g_majorWeights
        try:
            data = await request.json()
            rankOrScore = data["rankOrScore"]
            score = data["score"]
            rank = data["rank"]
            province = data["province"]
            ptype = data["type"]
            if ptype == "理科":
                ptypeid = 1
            elif ptype == "文科":
                ptypeid = 2
            elif ptype == "综合":
                ptypeid = 3
            else:
                raise Server.BadRequest("Unknown type: %s" % ptype)

            expectedMajor = data["expectedMajor"]

            if rankOrScore == "score":
                ret = self.getListByScore(score, province, ptypeid,
                                          expectedMajor)
            elif rankOrScore == "rank":
                score = self.getScoreByRank(rank, province, ptypeid)

                if score == None:
                    raise Server.BadRequest("暂无数据")

                ret = self.getListByScore(score, province, ptypeid,
                                          expectedMajor)
            return web.json_response(ret)
        except Server.BadRequest as e:
            return self.onError("%s" % (str(e)))
        except Exception as e:
            return self.onError("%s: %s" % (str(type(e)), str(e)))

    def run(self, host: str, port: int):
        self.app = web.Application()
        self.app.add_routes([web.post('/', self.handle)])

        web.run_app(self.app, host=host, port=port)


# async def handle(request):
#     class BadRequest(Exception):
#         def __init__(self, *args, **kwargs):
#             Exception.__init__(self, *args, **kwargs)

#     global g_schoolscore

#     try:
#         data = await request.post()
#         print(data)

#         pid = data["province_id"]
#         tid = data["type_id"]
#         val = data["value"]
#         val_type = data["value_type"]
#         major_type = data["major"]

#         pid = int(pid)
#         tid = int(tid)
#         val = int(val)
#         val_type = int(val_type)

#         if val_type != 0:
#             raise BadRequest("排名推荐尚未实现")

#         if major_type != "":
#             raise BadRequest("专业筛选功能尚未实现")

#         data = [[], [], []]
#         # 0:冲刺 1:稳健 2:保底
#         for sid in g_schoolscore:
#             school = g_schoolscore[sid]
#             try:
#                 score = school[str(pid)][str(tid)]
#             except KeyError:
#                 pass
#             else:
#                 if score[1] > 0:
#                     diff = val - score[0] / score[1]
#                     p = getProbability(diff)
#                     print(diff)
#                     if p < 0.4:
#                         datatype = 0
#                     elif p < 0.95:
#                         datatype = 1
#                     else:
#                         datatype = 2

#                     data[datatype].append([sid, getWeight(diff), p])
#         data[0].sort(key=lambda x: x[1], reverse=True)
#         data[1].sort(key=lambda x: x[1], reverse=True)
#         data[2].sort(key=lambda x: x[1], reverse=True)

#         ret = {"code": 0, "msg": "查询成功", "data": {"length": 9, "values": []}}

#         for school in data[0][:3]:
#             ret["data"]["values"].append({
#                 "schoolID": school[0],
#                 "info": "冲刺",
#                 "p": school[2]
#             })
#         for school in data[1][:3]:
#             ret["data"]["values"].append({"schoolID": school[0], "info": "稳健"})
#         for school in data[2][:3]:
#             ret["data"]["values"].append({"schoolID": school[0], "info": "保底"})

#         return web.json_response(ret)
#     except Exception as e:
#         print(type(e), e)
#         # raise e
#         return on_error(request, 1, str(type(e)) + ' ' + str(e))

if __name__ == "__main__" or True:
    server = Server("schoolInfo.json", "predict_x.json", "rank.json")
    server.run("127.0.0.1", 8080)
