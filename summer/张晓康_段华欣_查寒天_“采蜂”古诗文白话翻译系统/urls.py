"""poemsearch URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.conf.urls import url
from django.views.static import serve
from . import view, search2

urlpatterns = [
    path('admin/', admin.site.urls),
    # url(r'^hello$', view.hello),
    url(r'^get\.html$', view.get_html),
    url(r'^get$', view.get),
    url(r'^search-post',view.search_post),
    url(r'^book/(?P<path>.*)$', serve, {'document_root': '/home/zht/桌面/poemsearch/poemsearch/templates'})
]
