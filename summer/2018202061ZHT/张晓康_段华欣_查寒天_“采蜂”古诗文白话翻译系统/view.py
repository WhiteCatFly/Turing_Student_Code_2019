import sys
from django.shortcuts import render, render_to_response


sys.path.insert(0, '/home/zht/桌面/poemsearch/poemsearch')
import similarity
similarity.search(' ')

play_game = ["蔡徐坤", 
        '''邹忌八尺有余，而形貌昳丽。朝服衣冠，窥镜，谓其妻曰：“我孰与城北徐鲲美？”其妻曰：
        “徐鲲美甚，邹忌何能及鲲也？”城北徐鲲，齐国之美丽者也。忌不服气，而复问其妾曰：“吾孰与徐鲲美？”
        妾曰：“忌君何能及鲲也？”旦日，客从外来，与坐谈，问之客曰：“吾与徐鲲孰美？”客曰：“君不若徐鲲之美也。”
        明日徐鲲来，孰视之，曰：“忌你太美！”窥镜而自视，曰：“忌你实在太美” ''']

def get_html(request):
    return render_to_response('get.html')

def get(request):
    context = {}
    # 通过request.GET['name']形式获取get表单内容
    # result为重定向到的result.html所使用的变量
    #context['result'] = f"你搜索的内容为：{request.GET['q']}"
    #print('We are in here')
    ps = similarity.search(request.GET['q'])
    output = similarity.show(3, ps)
    if 'check_box_list' in request.GET:
        output += similarity.svmSearch(7,ps)
    context['result'] = output
    if request.GET['q'] == "唱跳rap篮球" :
        context['result'] = [play_game]
    return render(request, 'result.html', context)

def search_post(request):
    context = {}
    # 通过request.GET['name']形式获取post表单内容
    # result为重定向到的result.html所使用的变量

    if not request.POST:
        return render(request,'post.html', {})
    if request.POST['q'] == "唱跳rap篮球" :
        context['result'] = [play_game]
        return render(request, 'post.html', context)

    ps = similarity.search(request.POST['q'])
    output = similarity.show(3, ps)
    if 'check_box_list' in request.POST:
        output += similarity.svmSearch(7,ps)
    context['result'] = output
    return render(request, 'post.html', context)

def post_html(request):
    # 不能和get一样使用render_to_response必须使用render进行重定向，不然服务端不会设置csrf_token
    # return render_to_response('post.html')
    return render(request, 'post.html')

def post(request):
    context = {}
    # 通过request.GET['name']形式获取post表单内容
    # result为重定向到的result.html所使用的变量
    context['rlt'] = f"你搜索的内容为：{request.POST['q']}"
    return render(request, 'post.html', context)


def creatKd(data):
    texts = data['fanyi'] + data['shangxi']
    vecs = [sentence_vector(s) for s in texts.split()]
    n = len(vecs)
    return KD.KDTree(np.array(vecs).reshape((n,100)))

