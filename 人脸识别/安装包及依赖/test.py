#!/usr/bin/env python
# coding=utf-8

import multiprocessing as mp
import os
from picamera import PiCamera
import time
import uuid

from com.aliyun.api.gateway.sdk import client as iotclient
from com.aliyun.api.gateway.sdk.http import request
from com.aliyun.api.gateway.sdk.common import constant
from aliyunsdkcore.client import AcsClient
from aliyunsdkfacebody.request.v20191230.SearchFaceRequest import SearchFaceRequest
from viapi.fileutils import FileUtils

def search(filename):
    client = AcsClient('LTAI4G6z2HM3Y4KMVt79aM7k', 'o9sOuCwdkSJ57iWYdd4EzVa3A2TO3d', 'cn-shanghai')
    file_utils = FileUtils("LTAI4G6z2HM3Y4KMVt79aM7k", "o9sOuCwdkSJ57iWYdd4EzVa3A2TO3d")
    print 'uploading...'
    PIC_ROOT = os.path.dirname(os.path.abspath(__file__))
    pix = filename.split('.')[1]
    oss_url = file_utils.get_oss_url(PIC_ROOT + "/pic/" + filename, "jpg", True)

    face_request = SearchFaceRequest()
    face_request.set_accept_format('json')

    face_request.set_DbName("myFaceDB")
    # request.set_ImageUrl("http://viapi-test.oss-cn-shanghai.aliyuncs.com/viapi-3.0domepic/facebody/RecognizeFace"
    #                     "/RecognizeFace1.png")
    face_request.set_ImageUrl(oss_url)
    face_request.set_Limit(1)

    response = client.do_action_with_exception(face_request)
    print str(response)

    iot_url = "/a123ml8t9gu2zqTT/bfjc5oUj7hE9BV"

    host = "http://4efd73d6c344454c9f1eab552d71964b-cn-shanghai.alicloudapi.com"

    cli = iotclient.DefaultClient(app_key="32569956", app_secret="0fa2b5d9f8ad25c32811dd3394ad6ddc")

    req_post = request.Request(host=host, protocol=constant.HTTPS, url=iot_url, method="POST", time_out=30000,
                               sign_with_body=False)
    bodyMap = {
        'id': str(uuid.uuid4()),
        'version': "1.0",
        'request': {
            'apiVer': "1.0.0"
        },
        'params': {
           'action': 'TEST_ACTION',
            'info': str(response)
        }
    }
    req_post.set_body(bodyMap)
    req_post.set_content_type(constant.CONTENT_TYPE_JSON)
    print(cli.execute(req_post))
    return str(response)

# Main ######################################################################

if __name__ == '__main__':
    camera = PiCamera()  # 得到摄像头实例
    camera.rotation = 180
    camera.start_preview()
    time.sleep(5)
    name = time.time()
    camera.resolution = (1024, 768)  # 设置分辨率
    camera.rotation = 180  # 控制摄像头旋转180度
    name_time = time.strftime("%Y%m%d%H%M%S", time.localtime(name))
    camera.capture('/home/pi/pic/' + name_time + '.jpg')
    camera.stop_preview()
    camera.close()
    search(name_time + '.jpg')

