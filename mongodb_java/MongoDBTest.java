/*
# ysoftman
# MongoDB 알아두기

# 참고 자료
# http://www.mongodb.org/display/DOCS/Replication
# http://en.wikipedia.org/wiki/MongoDB
# http://docs.mongodb.org/manual/faq/developers/#when-does-mongodb-write-updates-to-disk
 
# Memory Mapped File 이란
# 가상메모리의 한부분으로 파일을 메모리에 매핑하여 사용함
# 따라서 메모리에 맵핑된 파일은 메모리처럼 다룬다.
# MongoDB 에서는 가상메모리 관리를 전적으로 OS 에 의존

# Write 발생시
# 메모리에 먼저 write 후 백그라운드 쓰레드로 1분 주기로 Disk 기록(write back)
# disk 기록 실패 발생시 데이터 유실로 인해 일관성이 깨질 수 있음

# Read 발생시 
# 메모리에 로딩해 놓은 상태에서 read 수행

# Mongodb 속도는 인덱스 사이즈와 메모리에 좌우
# 메모리가 가득차서 가상메모리리를 사용할 경우, 데이터 처리속도 급감

# 서버 역할
# master server : 읽기, 쓰기로 사용 
# slave server : 읽기로만 사용, master 복제(백업)하고 있음
# arbiter server : master, slave 체크하고, 장애 발생시 slave 하나를 master 로 선정

# 기본적으로 master 만 write 를 수행하기 때문에 master 에 write 부하가 생김
# 이를 해결하기 위해서 데이터를 분산저장하는 auto-sharding 을 이용

# 2가지 Replication 방법 제공
# master-slave
# master 1대에 n대의 slave 가 붙어서 복제한다.
# slave 는 master 의 데이터를 카피하고 읽기전용이나 백업용도로만 사용한다.(not writes)
                 
# replica-set
# mongodb 1.6 이후부터 지원되기 시작했다.
# master-slave 구조에 arbiter(master, slave 의 heartbeat 를 체크하여 master 장애 발생시 자체적으로 slave 중 하나를 master 를 선정) 노드를 추가하여 fail-over 지원
*/

/*
# ysoftman
# MongoDB 구성 하기
# 구성도 http://www.mongodb.org/display/DOCSKR/Introduction
# client(application) 은 router Server 에 접속해서 쿼리를 요청하면 된다.
# client 가 write 요청을 했다면 router 는 master mongodb 로, read 했다면 slave mongodb 로 안내한다.
# mongodb 서버에 1000을 더한 포트로 접속하면 MongoDB 모니터링 웹을 볼 수 있다.(http://127.0.0.1:56555)

# mkdir ysoftman_db_master
# mkdir ysoftman_db_slave
# mkdir ysoftman_db_config

# .lock 파일 삭제
rm -rfv ./ysoftman_db_master/*.lock
rm -rfv ./ysoftman_db_slave/*.lock
rm -rfv ./ysoftman_db_config/*.lock

# master mongoDB Server 시작하기
bin/mongod --master --dbpath ./ysoftman_db_master --port 10010 > /dev/null &

# slave mongoDB Server 시작하기(master 와 다른 장비에서)
#bin/mongod --slave --dbpath ./ysoftman_db_slave --port 10020 --source 10.10.10.100:10010 --autoresync > /dev/null &

# config mongoDB Server 시작하기
bin/mongod --dbpath ./ysoftman_db_config --port 10001 > /dev/null &

# router Server 시작하기
bin/mongos --port 10000 --configdb 10.10.10.100:10001 > /dev/null &

# router Server 접속해서 Sharding 하기
bin/mongo 10.10.10.100:10000


# admin db 를 사용해서 설정해야 한다.
use admin;

# shard 추가하기, router 랑 같은 머신의 shard 를 사용할 수 있도록 옵션 명시
# 실제 사용시에는 router 랑 다른 머신의 shard 를 사용해야 한다.
db.runCommand({addshard:"10.10.10.100:10010", allowLocal:true});

# database 단위에서 sharding enable 하기
db.runCommand({enablesharding:"testdb"});

# col1 collection 의 _id 별로 자동 분산되어 저장하도록 하기
db.runCommand({shardcollection:"testdb.col1", key:{"_id":1}});

# sharding 상태확인
db.printShardingStatus();

# shard 삭제하기
db.runCommand({removeshard:"10.10.10.100:10010"});

# testdb 사용하기(DB 를 미리 생성하지 않는다.)
use testdb

# routerinfo 콜렉션 생성
db.createCollection("routerinfo");

# 예) JSON 형식으로 정보 추가
db.routerinfo.save(
{"id": "1234",
"name": "ysoftman", 
"timestamp": 12345,
"userkey": "UserNo",
"metainfo": {"list":[ 
					{"name":"UserNo", "desc":"사용자", "type":"int"},
					{"name":"Item", "desc":"아이템", "list":[
														{"name":"a", "desc":"아이템1"},
														{"name":"b", "desc":"아이템2"}
														]
					},
					{"name":"phone", "desc":"전화번호", "type":"int"},
					{"name":"name", "desc":"이름"},
					{"name":"trash", "desc":"쓰레기"},
					{"name":"Map", "desc":"맵", "pk":"MapID", "array":[
																	{"name":"MapID", "desc":"맵번호", "type":"int"},
																	{"name":"MinScore", "desc":"최소점수", "type":"int"},
																	{"name":"MaxScore", "desc":"최대점수", "type":"int"}
																]
					}
					]
			}
}
);

# Mongodb 쿼리 예
# SQL to mongdo mapping chart http://www.mongodb.org/display/DOCS/SQL+to+Mongo+Mapping+Chart
# SQL to Shell to C++ http://www.mongodb.org/pages/viewpage.action?pageId=21270051
# Manual http://www.mongodb.org/display/DOCS/Manual
# MySQL term	Mongo term
# database	database
# table		collection
# index		index
# row		BSON document
# 하나의 document 최대 크기 16MB
 
# 클라이언트 접속하기
bin\mongo 10.10.10.100:10000
 
# 도움말
help()
 
# Database 목록보기
show dbs

# testdb 사용하기(DB 를 미리 생성하지 않는다.)
use testdb
 
# 현재 사용중인 DB 확인
db.getName()

# 현재 Databse 컬렉션 보기
show collections
 
# 크기 제한 설정하여 컬레션 생성 size: 크기, max: 최대 개수
#db.createCollection("col1", {capped:true, size:100000, max: 1000});
db.createCollection("col1");
 
# 컬렉션 이름이 숫자로 시작하면 
db["1234"]
# 컬렉션 이름이 문자로 시작하면
db["col1"] 또는 db.col1
 
# 컬렉션 상태 보기
db.col1.validate()

# 켈렉션 삭제하기
db.col1.drop()

# col1 라는 컬렉션에 Name, URL, LastUpdate 등의 데이터를 저장하기(insert() or save())
db.col1.save({UserNo:0, Map:[{MapID:1, Score:100}, {MapID:2, Score:200}]});

# col1 의 다큐먼트 개수 파악하기
db.col1.count()

# col1 의 모든 다큐먼트 검색하기
db.col1.find()

# col1 의 모든 다큐먼트 검색하기(들여쓰기하여 출력)
db.col1.find().pretty()

# UserNo 가 555 인 다큐먼트 찾기
db.col1.find({UserNo:555})

# UserNo 가 555 인 다큐먼트를 찾아서 Map.MapID 필드만 보여주기
db.col1.find({"UserNo":555}, {"Map.MapID":1});

# UserNo 가 555 인 다큐먼트를 찾아서 _id 는 제외하고 Map.MapID 필드만 보여주기
db.col1.find({"UserNo":555}, {_id:0, "Map.MapID":1});

# col1 의 모든 다큐먼트 검색하기(_id 로 오름차순 정렬로 보여주기 -1이면 내림차순)
db.col1.find().sort({_id:1})

# Map.MapID 의 값이 10 인 다큐먼트 개수
db.col1.find({"Map.MapID":10}).count()

# Map.MapID 의 값이 100 보다 큰거나 같은 다큐먼트 개수
db.col1.find({"Map.MapID":{$gte:100}}).count()

# UserNo 가 555 이고 Map 배열의 첫번째 MapID 값을 1234 로 변경하기(조건에 해당하는 내용이 없으면 다큐먼트 하나가 추가된다)
db.col1.update({"UserNo":555}, {$set:{"Map.0.MapID":1234}}, true);

# UserNo 가 555 이고 Map 배열의 100번째 MapID 값을 삭제하기
db.col1.update({"UserNo":555}, {$unset:{"Map.100.MapID":1}});

# UserNo 가 555 이고 Map 배열중 MapID 가 2인 곳을 찾아내어 123 값으로 설정한다.
db.col1.update({UserNo:555, "Map.MapID":2}, {$set:{"Map.$.MapID":123}})

# UserNo 가 555 이고 Map 배열에 object 추가(array 필드에 대해서만 사용할 수 있다)
db.col1.update({UserNo:555}, {$push:{Map:{"MapID":333, "MinScore":300, "MaxScore":500}}})

# 현재 컬렉션의 데이터 하나 삭제하기(검색 결과 id로 지운다)
db.col1.remove({_id:ObjectId("4d5a1ad2e812000000000515")})

# 현재 컬렉션의 모든 document 삭제
db.col1.remove()

# 인덱스 생성(1:ascending, -1:descending)
db.col1.ensureIndex({"UserNo":1});

# 현재 인덱스 확인(db.system.indexes.find() 전체 인덱스 확인)
db.col1.getIndexes()

# 인덱스 삭제
db.col1.dropIndexes()

# db 상태 확인(data, index 사이즈 등...)
db.stats();

# 서버 상태 확인
db.serverStatus()
db.serverStatus().mem
db.serverStatus().extra_info

# 클라이언트 종료
exit
*/

/*
////////////////////////////////////////////////////////////////////////////////
// ysoftman
// MongoDB Test - Stored JavaScript 사용
////////////////////////////////////////////////////////////////////////////////
# 클라이언트 접속하기
bin\mongo 10.10.10.100:10000

# testdb 사용하기(DB 를 미리 생성하지 않는다.)
use testdb
 
# collection 의 document 전체 삭제
function test1 () {
	db.col1.drop();
	return true;
}
db.eval(test1);


// insert 하기 데이터 크기가 4GB 를 넘어가서 64bit mongodb 사용
// 100만개(mongovue)			경과시간: 2분 35초	DB크기: 0.5GB
// 1000만개(mongovue)			경과시간: 47분15초	DB크기: 5.95GB	(인덱스 메모리에 저장되어 사용)
function test2() {
	for (var i=1; i<=1000000; i++)
	{
		str = {
		Name:"HongGilDong",
		Mobile:"010-123-4567",
		"E-Mail":"ysoftman@naver.com",
		Clan:"Best_of_Best",
		Inventory:{
			Sword:"HighLevel",
			Robe:"MediumLevel",
			Potions:{
				HP_Potion:"SmallSize",
				MP_Potion:"BigSize"
				},
			PortalScroll:"1"
			},
		Status:{
			HP:i,
			MP:i
			},
		Skill:{
			FireBall:"1",
			Blizzard:"2"
			}
		}
		
		db.col1.save(str);
	}
	return 1;
}
db.eval(test2);

# memory dependent 하기 때문에 page fault 가 발생하지 않을 정도의 메모리가 있을 경우를 가정
# 100만개시 index 사용 없이 1초내 검색 완료
# 1000만개시 index 사용 없이 약 2분 소요, index 사용시 1초내
# Status.HP 가 123 인것 
db.col1.find({"Status.HP":123}).count()

# Status.HP 가 1 보다 큰것
# 100만개시 index 사용 없이 1초내 검색 완료
# 1000만개시 index 사용 없이 약 2분 소요, index 사용시 1초내
db.col1.find({"Status.HP":{$gt:1}}).count()

# Status.HP 가 1 보다 작은것
# 100만개시 index 사용 없이 1초내 검색 완료
# 1000만개시 index 사용 없이 약 2분 소요, index 사용시 1초내
db.col1.find({"Status.HP":{$lt:1000000}}).count()

# Status.HP 가 1 보다 큰거나 같은것
db.col1.find({"Status.HP":{$gte:1}}).count()

# Status.HP 가 1 보다 작거나 같은것
db.col1.find({"Status.HP":{$gte:1}}).count()
*/

//////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Mongo Client Test (Java)
// mongo-java-driver-2.9.3.jar 사용
//////////////////////////////////////////////////////////////////////////////////
import java.util.ArrayList;
import java.net.UnknownHostException;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.Mongo;
import com.mongodb.MongoException;


public class MongoDBTest
{	
	public static void main(String[] args )
	{
		InsertData("10.10.10.100", 10000, "testdb", "col1");
		//UpdateData("10.10.10.100", 10000, "testdb", "col1");
		//SearchData("10.10.10.100", 10000, "testdb", "col1");
	}
	
	public static void InsertData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();
		try
		{
			// mongodb 연결
			Mongo con = new Mongo(ip, port);

			// db 사용하기
			DB db = con.getDB(dbname);

			// collection 사용하기
			DBCollection collection = db.getCollection(colname);


			// 사용자들에 대해서
			for (int i=1; i<=1000000; i++)
			{
				// document 로 저장할 데이터 생성
				BasicDBObject doc = new BasicDBObject();
				// key, value 형식 데이터 추가
				doc.put("UserNo", i);
				// 100 개의 맵,스코어 정보
				ArrayList<BasicDBObject> arraydata = new ArrayList<BasicDBObject>();
				for (int j=1; j<=100; j++)
				{
					BasicDBObject doc2 = new BasicDBObject("MapID", j);
					doc2.put("Score", j);
					arraydata.add(doc2);
				}
				doc.append("Map", arraydata);

				// 실제 데이터 저장
				collection.save(doc);

				// 진행상황 파악을 위해
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}
		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("insert time: "+timeresult+"sec");
		
	}
	
	public static void UpdateData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();
		try
		{
			// mongodb 연결
			Mongo con = new Mongo(ip, port);

			// db 사용하기
			DB db = con.getDB(dbname);

			// collection 사용하기
			DBCollection collection = db.getCollection(colname);


			// 사용자들에 대해서
			for (int i=1; i<=100000; i++)
			{
				BasicDBObject doc = new BasicDBObject();
				doc.put("UserNo", i);
				
				BasicDBObject doc2 = new BasicDBObject();
				doc2.append("$set", new BasicDBObject().append("Map.0.Score", 1234));
				
				// UserNo 가 555 인 사용자의 Map 배열의 첫번째 MapID 값을 1234 로 변경하기(조건에 해당하는 내용이 없으면 다큐먼트 하나가 추가된다)
				// db.col1.update({"UserNo":555}, {$set:{"Map.0.MapID":1234}}, true);
				// 실제 데이터 업데이트
				collection.update(doc, doc2, false, true);

				// 진행상황 파악을 위해
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}
		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("update time: "+timeresult+"sec");
		
	}
	
	public static void SearchData(String ip, int port, String dbname, String colname)
	{
		long timebefore = 0;
		long timeafter = 0;
		long timeresult = 0;
		
		timebefore = System.currentTimeMillis();		
		try
		{
			// mongodb 연결
			Mongo con = new Mongo(ip, port);

			// db 사용하기
			DB db = con.getDB(dbname);

			// collection 사용하기
			DBCollection collection = db.getCollection(colname);


			// 사용자들에 대해서
			for (int i=1; i<=10000; i++)
			{
				BasicDBObject doc = new BasicDBObject();
				// 사용자 한명의 전체 데이터 검색
				doc.put("UserNo", i);
				// 사용자 한명의 Map.MaID == 10 것 검색
				//doc.put("Map.MapID", 55);
				DBCursor cursor = collection.find(doc);
				// 쿼리 결과 연속해서 나타내기
				while (cursor.hasNext())
				{
					// 속도 측정을 위해 콘솔로 출력하지 않는다.
					//System.out.println(cursor.next());
					cursor.next();
				}
				// 진행상황 파악을 위해
				if (i%1000 == 0)
				{
					System.out.println("Data Count:"+i);
				}
			}

		} 
		catch (UnknownHostException e)
		{
			e.printStackTrace();	
		}
		catch (MongoException e)
		{
			e.printStackTrace();
		}
		timeafter = System.currentTimeMillis();
		timeresult = (timeafter-timebefore)/1000;
		System.out.println("search time: "+timeresult+"sec");		
	}	
}


