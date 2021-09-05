# -*- coding: utf-8 -*-
# This file is auto-generated, don't edit it. Thanks.
import sys

from typing import List
from Tea.core import TeaCore

from alibabacloud_facebody20191230.client import Client as facebody20191230Client
from alibabacloud_tea_openapi import models as open_api_models
from alibabacloud_facebody20191230 import models as facebody_20191230_models
from alibabacloud_tea_console.client import Client as ConsoleClient
from alibabacloud_tea_util.client import Client as UtilClient


class Sample:
    def __init__(self):
        pass

    @staticmethod
    def create_client(
        access_key_id: str,
        access_key_secret: str,
    ) -> facebody20191230Client:
        """
        使用AK&SK初始化账号Client
        @param access_key_id:
        @param access_key_secret:
        @return: Client
        @throws Exception
        """
        config = open_api_models.Config(
            # 您的AccessKey ID,
            access_key_id=access_key_id,
            # 您的AccessKey Secret,
            access_key_secret=access_key_secret
        )
        # 访问的域名
        config.endpoint = 'facebody.cn-shanghai.aliyuncs.com'
        return facebody20191230Client(config)

    @staticmethod
    def main(
        args: List[str],
    ) -> None:
        client = Sample.create_client('ACCESS_KEY_ID', 'ACCESS_KEY_SECRET')
        create_face_db_request = facebody_20191230_models.CreateFaceDbRequest()
        resp = client.create_face_db(create_face_db_request)
        ConsoleClient.log(UtilClient.to_jsonstring(TeaCore.to_map(resp)))

    @staticmethod
    async def main_async(
        args: List[str],
    ) -> None:
        client = Sample.create_client('ACCESS_KEY_ID', 'ACCESS_KEY_SECRET')
        create_face_db_request = facebody_20191230_models.CreateFaceDbRequest()
        resp = await client.create_face_db_async(create_face_db_request)
        ConsoleClient.log(UtilClient.to_jsonstring(TeaCore.to_map(resp)))


if __name__ == '__main__':
    Sample.main(sys.argv[1:])
