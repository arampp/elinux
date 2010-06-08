from django.conf.urls.defaults import *

urlpatterns = patterns('plantguard.storedata.views',
  (r'^(?P<data>\d+)/(?P<password>.+)/$', 'storedata'),
)
   
