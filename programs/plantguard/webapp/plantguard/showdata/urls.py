from django.conf.urls.defaults import *

urlpatterns = patterns('plantguard.showdata.views',
  (r'^$', 'home'),
  (r'^show/(?P<days>\d+)/$', 'show_diagrams'),
  (r'^store/(?P<data>\d+)/(?P<password>.+)/$', 'storedata'),
)
