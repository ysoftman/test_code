using System;
using System.Collections.Generic;
// LitJson 다운로드 --> http://lbv.github.io/litjson/
using LitJson;

// ysoftman
// LitJson 라이브러리 테스트
namespace LitJsonTest
{
    public class InfoData
    {
        // JSON 의 키와 같은 이름을 변수로 사용해야 한다.
        public int id { get; set; }
        public int count { get; set; }
        public string mesg { get; set; }

    }
    public class UserData
    {
        // JSON 의 키와 같은 이름을 변수로 사용해야 한다.
        public string name { get; set; }
        public int age { get; set; }
        public Dictionary<string, InfoData> info { get; set; }
    }


    class Program
    {
        static void Main(string[] args)
        {

            string strJson = @"
            {
                ""name"": ""ysoftman"",
                ""age"": 20,
                ""info"": {
                    ""key1"": {
                        ""id"": 123,
                        ""count"": 1000,
                        ""mesg"": ""message1""
                    },
                    ""key2"": {
                        ""id"": 456,
                        ""count"": 500,
                        ""mesg"": ""message2""
                    }
                }
            }";

            // UserData 형으로 읽어오기
            UserData user = LitJson.JsonMapper.ToObject<UserData>(strJson);


            // UserData 에 담긴 내용 출력해보기
            System.Console.WriteLine("user.name : {0}\n" +
                "user.age : {1}\n"
                , user.name, user.age);
            foreach (KeyValuePair<string, InfoData> info in user.info)
            {
                System.Console.WriteLine("user.info[{0}].id : {1}\n" +
                    "user.info[{0}].count : {2}\n" +
                    "user.info[{0}].mesg : {3}\n",
                    info.Key.ToString(), info.Value.id, info.Value.count, info.Value.mesg);
            }

        }
    }
}
