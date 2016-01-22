package com.Android_ServerMon;

//import java.util.*;
//import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

import android.util.Log;

/**
 *	@brief							HTTP 프로토콜 포맷에 맞춰 request/response 를 수행한다.
 *	@author							윤병훈
 *	@param							None
 *	@return							None
 */
public class HttpExecutor
{
	private String m_Recv;

	public String m_IP;
	public int m_Port;
	public long m_MemberNum;

	/**
	 *	@brief							HttpExecutor 생성자(비인증모드일때 멤버넘버 사용)
	 *	@author							윤병훈
	 *	@param			ip				Server IP
	 *	@param			port			Server Port
	 *	@param			membernum		멤버 넘버
	 *	@return							None
	 */
	public HttpExecutor(String ip, int port, long membernum)
	{
		m_IP = ip;
		m_Port = port;
		m_MemberNum = membernum;
	}

	/**
	 *	@brief							암호화하기
	 *	@author							윤병훈
	 *	@param			key				암호화에 사용할 키
	 *	@param			iv				암호화에 사용할 초기 벡터
	 *	@param			Plain			암호화할 데이터
	 *	@return							암호화된 데이터
	 */
	private String EnCode(String key, String iv, String Plain)
	{
		if (Plain.length() <= 0)
		{
			return null;
		}

		try
		{
			SecretKeySpec skey = new SecretKeySpec(key.getBytes("utf-8"), "AES");

			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			cipher.init(Cipher.ENCRYPT_MODE, skey, new IvParameterSpec(iv.getBytes("utf-8")));
			byte[] encrypted = cipher.doFinal(Plain.getBytes("utf-8"));

			// Base64 로 인코딩한다.
			// 안드로이드에서 지원하지 않음
			//String result = com.sun.org.apache.xerces.internal.impl.dv.util.Base64.encode(encrypted);
			// Base64 공개 라이브러리 사용
			String result = Base64.encodeBytes(encrypted);

			return result;
		}
		catch (Exception e)
		{
			System.out.println("Error : " + e.toString());
			e.printStackTrace();
			return "";	
		}
	}

	/**
	 *	@brief							복호화하기
	 *	@author							윤병훈
	 *	@param			key				복호화에 사용할 키
	 *	@param			iv				복호화에 사용할 초기 벡터
	 *	@param			Cipher			복호화할 데이터
	 *	@return							복호화된 데이터
	 */
	private String DeCode(String key, String iv, String CipherString)
	{
		if (CipherString.length() <= 0)
		{
			return "";
		}

		try
		{
			// 암호화된 결과는 Base64Encoding 된 상태이다.
			//byte[] CipherBytes = com.sun.org.apache.xerces.internal.impl.dv.util.Base64.decode(CipherString);
			byte[] CipherBytes = Base64.decode(CipherString);

			SecretKeySpec skey = new SecretKeySpec(key.getBytes("utf-8"), "AES");

			Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
			cipher.init(Cipher.DECRYPT_MODE, skey, new IvParameterSpec(iv.getBytes("utf-8")));
			byte[] decrypted = cipher.doFinal(CipherBytes);

			String result = new String(decrypted, "utf-8");

			return result;

		}
		catch (Exception e)
		{
			String errmsg = "Error : " + e.toString();
			System.out.println(errmsg);
			e.printStackTrace();
			return "";	
		}

	}

	/**
	 *	@brief							http 포맷으로 전송
	 *	@author							윤병훈
	 *	@param			cmd				전송명령 형태(POST , GET, DELETE, PUT)
	 *	@param			path			대상 경로
	 *	@param			data			대상 데이터
	 *	@return							성공하면 0 리턴
	 */
	private int HttpRequest(String cmd, String path, String data)
	{
		// Session 사용 
		Session session = new Session();
		session.Connect(m_IP, m_Port);

		// 현재 파일 인코딩 값을 확인
		//String enc = System.getProperty("file.encoding");
		//System.out.println("file.encoding : " + enc);

		// String 일때 문자의 길이(글자 하나당 1개로 취급된다.)
		//System.out.println("udata.length() : " + udata.length());


		// String 을 바이트로 읽어와 바이트 길이로 설정
		byte[] bytes = null;
		try
		{
			bytes = data.getBytes("utf-8");
		}
		catch (Exception e)
		{
			System.out.println("Error : " + e.toString());
			e.printStackTrace();
			return -1;	
		}
		//System.out.println("bytes.length : " + bytes.length);
		int len = bytes.length;


//		http 헤더 예
//		GET /MobileOmok/XMapMemberInfo/4105000000102846 HTTP/1.1
//		Host: 10.77.30.68:10000
//		Connection: keep-alive
//		Cache-Control: max-age=0
//		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
//		User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.71 Safari/537.36
//		Accept-Encoding: gzip,deflate,sdch
//		Accept-Language: ko-KR,ko;q=0.8,en-US;q=0.6,en;q=0.4

		// 현재 data 는 사용하지 않음
		String msg = cmd + " /"+ path + " HTTP/1.1\r\n" +
				"Host:" + m_IP + ":" + m_Port + "\r\n" +
				"Connection: keep-alive\r\n" +
				"Content-Type: application/json\r\n" +
				"charset: \"utf-8\"\r\n" +
				"Content-Length: " + len + "\r\n" +
				"\r\n" +
				data;

		//System.out.println(msg);

		// String 형의 msg 를 바이트로 바꾸어 전송하도록 한다.
		byte[] sendbytes = null;
		try
		{
			sendbytes = msg.getBytes("utf-8");
		}
		catch (Exception e)
		{
			System.out.println("Error : " + e.toString());
			e.printStackTrace();
			return -1;
		}
		session.Send(sendbytes);

		// 수신한다.
		String temp = "";
		temp = session.Receive(3000);
		// 문자열 공백 제거
		m_Recv = temp.trim();

		//System.out.println(m_Recv);

		session.Disconnect();

		return 0;
	}

	/**
	 *	@brief							최근에 수신 받은 에러 코드를 리턴
	 *	@author							윤병훈
	 *	@param							None
	 *	@return							최근에 수신 받은 에러 코드
	 */
	public int GetLastErrorCode()
	{
		int errcode = 0;
		String temp = "";
		String keyword = "errcode\": ";
		// 수신된 메시지중 에러메시지 부분은 예를 들어 아래와 같이 표현된다.
		// "errcode": 917509, "errmessage": ...

		if (m_Recv == null)
		{
			errcode = -1;
			return errcode;
		}
		// errmessage: " 로 시작하는 부분 다음을 시작점으로 잡는다.
		int start_idx = m_Recv.indexOf(keyword) + keyword.length();
		// 이제 시작점부터 , 이 나오는 부분을 끝점으로 잡는다.
		int end_idx = m_Recv.indexOf(",", start_idx);
		if (start_idx < end_idx)
		{
			temp = m_Recv.substring(start_idx, end_idx);
			errcode = Integer.parseInt(temp);
			if (errcode != 0 && errcode != 1)
			{
				errcode = -2;
			}
		}
		else
		{
			errcode = -3; // TIMEOUT
		}

		return errcode;
	}

	/**
	 *	@brief							최근에 수신 받은 메시지중 에러메시지를 리턴
	 *	@author							윤병훈
	 *	@param							None
	 *	@return							최근에 수신 받은 메시지
	 */
	public String GetLastErrorMsg()
	{
		String temp = "";
		String keyword = "errmessage\": \"";
		// 수신된 메시지중 에러메시지 부분은 예를 들어 아래와 같이 표현된다.
		// "errmessage": "aaa"

		if (m_Recv == null)
		{
			temp = "ERROR_INVALID_HANDLE";
			return temp;
		}
		// errmessage: " 로 시작하는 부분 다음을 시작점으로 잡는다.
		int start_idx = m_Recv.indexOf(keyword) + keyword.length();
		// 이제 시작점부터 " 이 나오는 부분을 끝점으로 잡는다.
		int end_idx = m_Recv.indexOf("\"", start_idx);
		if (start_idx < end_idx)
		{
			temp = m_Recv.substring(start_idx, end_idx);
		}
		else
		{
			temp = "ERROR_TIMEOUT";
		}
		return temp;
	}

	/**
	 *	@brief							xml_expression 체크하여 엔터가 들어있으면 제거한다.(http 통신시 xml_expression 은 한줄로 표현되어야 한다.)
	 *									xml_expression 체크하여 " 는 \" 로 표현한다.(http 통신시 " 는 backslash quotation \" 으로 표시되어야 한다.)
	 *	@author							윤병훈
	 *	@param			xml_expression	쿼리 내용
	 *	@return							체크된 xml_expression;
	 */
	private String CheckXMLExpression(String xml_expression)
	{
		// 엔터제거
		xml_expression = xml_expression.replaceAll("\n", "");
		// " 는 \" 로 변경
		// replaceAll 두 파라미터가 정규식을 사용한다.
		// \" 를 표현한기 위해서 \\ \\ \" 로 나타낸다. 
		// \\\\\"  ===> \"
		xml_expression = xml_expression.replaceAll("\"", "\\\\\"");

		return xml_expression;
	}


	/**
	 *	@brief							Get 쿼리 요청하기
	 *	@author							윤병훈
	 *	@param			path			쿼리 내용
	 *	@param			result			쿼리 결과
	 *	@return							성공하면 0 리턴
	 */		
	public int GetData(String path, String[] result)
	{
		// 암호화 하기
		//String EncodedStr = EnCode(Common.AES_Key, Common.AES_InitialVector, query);

		String temp = "abcd";
		String data = "{\r\n" + 
				"\"userdata\":" + "\"" + temp + "\"," + "\r\n" +
				"}";
		path += "/" + m_MemberNum;
		HttpRequest("GET", path, data);

		result[0] = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
		if (m_Recv == null)
		{
			return -1;
		}

		//Log.d("ysoftman", m_Recv);
		result[0] = m_Recv;
		
		
//		String temp = "xml_expression\": \"";
//		int start_idx = m_Recv.indexOf(temp) + temp.length();
//		int end_idx = m_Recv.lastIndexOf("\"");
//		if (start_idx >= end_idx)
//		{
//			return -2;
//		}
//		temp = m_Recv.substring(start_idx, end_idx);
//
//		// 결과가 없으면 
//		if (temp.length() < 1)
//		{
//			result[0] = "";
//		}
//		else
//		{
//			// AES 테스트
//			//String a = "암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n암호(AES) 테스트입니다. 이 문장이 보이면 암호/복호화가 정상적인것입니다.\n";
//			//String b = EnCode(AES_Key, AES_InitialVector, a);
//			//System.out.println(b);
//			//String c = DeCode(AES_Key, AES_InitialVector, b);
//			//System.out.println(a);
//
//
//			//암호 풀기(복호화)
//			String DecodedStr = DeCode(Common.AES_Key, Common.AES_InitialVector, temp);
//
//			// \" 을 " 로 바꿔준다.
//			DecodedStr = DecodedStr.replaceAll("\\\\\"", "\"");
//			//System.out.println("result: "+ str);
//			result[0] = DecodedStr;
//		}

//		return GetLastErrorCode();
		
		return 0;
	}

}

