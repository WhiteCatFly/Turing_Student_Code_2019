# -*- coding: utf-8 -*-

from django.shortcuts import render
from django.views.decorators import csrf

def post_html(request):
    # 不能和get一样使用render_to_response必须使用render进行重定向，不然服务端不会设置csrf_token
    # return render_to_response('post.html')
    return render(request, 'post.html')

def search_post(request):
    context = {}
    # 通过request.GET['name']形式获取post表单内容
    # result为重定向到的result.html所使用的变量
    if request.POST:
        context['result'] = [['1','2'],['3','4'],['5','6'],['1','2'],['3','4'],['5','6'],['1','2'],['3','4'],['5','6']]
    return render(request, 'post.html', context)