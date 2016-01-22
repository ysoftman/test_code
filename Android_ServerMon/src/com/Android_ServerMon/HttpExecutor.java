package com.Android_ServerMon;

//import java.util.*;
//import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;

import android.util.Log;

/**
 *	@brief							HTTP �������� ���˿� ���� request/response �� �����Ѵ�.
 *	@author							������
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
	 *	@brief							HttpExecutor ������(����������϶� ����ѹ� ���)
	 *	@author							������
	 *	@param			ip				Server IP
	 *	@param			port			Server Port
	 *	@param			membernum		��� �ѹ�
	 *	@return							None
	 */
	public HttpExecutor(String ip, int port, long membernum)
	{
		m_IP = ip;
		m_Port = port;
		m_MemberNum = membernum;
	}

	/**
	 *	@brief							��ȣȭ�ϱ�
	 *	@author							������
	 *	@param			key				��ȣȭ�� ����� Ű
	 *	@param			iv				��ȣȭ�� ����� �ʱ� ����
	 *	@param			Plain			��ȣȭ�� ������
	 *	@return							��ȣȭ�� ������
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

			// Base64 �� ���ڵ��Ѵ�.
			// �ȵ���̵忡�� �������� ����
			//String result = com.sun.org.apache.xerces.internal.impl.dv.util.Base64.encode(encrypted);
			// Base64 ���� ���̺귯�� ���
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
	 *	@brief							��ȣȭ�ϱ�
	 *	@author							������
	 *	@param			key				��ȣȭ�� ����� Ű
	 *	@param			iv				��ȣȭ�� ����� �ʱ� ����
	 *	@param			Cipher			��ȣȭ�� ������
	 *	@return							��ȣȭ�� ������
	 */
	private String DeCode(String key, String iv, String CipherString)
	{
		if (CipherString.length() <= 0)
		{
			return "";
		}

		try
		{
			// ��ȣȭ�� ����� Base64Encoding �� �����̴�.
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
	 *	@brief							http �������� ����
	 *	@author							������
	 *	@param			cmd				���۸�� ����(POST , GET, DELETE, PUT)
	 *	@param			path			��� ���
	 *	@param			data			��� ������
	 *	@return							�����ϸ� 0 ����
	 */
	private int HttpRequest(String cmd, String path, String data)
	{
		// Session ��� 
		Session session = new Session();
		session.Connect(m_IP, m_Port);

		// ���� ���� ���ڵ� ���� Ȯ��
		//String enc = System.getProperty("file.encoding");
		//System.out.println("file.encoding : " + enc);

		// String �϶� ������ ����(���� �ϳ��� 1���� ��޵ȴ�.)
		//System.out.println("udata.length() : " + udata.length());


		// String �� ����Ʈ�� �о�� ����Ʈ ���̷� ����
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


//		http ��� ��
//		GET /MobileOmok/XMapMemberInfo/4105000000102846 HTTP/1.1
//		Host: 10.77.30.68:10000
//		Connection: keep-alive
//		Cache-Control: max-age=0
//		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
//		User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.71 Safari/537.36
//		Accept-Encoding: gzip,deflate,sdch
//		Accept-Language: ko-KR,ko;q=0.8,en-US;q=0.6,en;q=0.4

		// ���� data �� ������� ����
		String msg = cmd + " /"+ path + " HTTP/1.1\r\n" +
				"Host:" + m_IP + ":" + m_Port + "\r\n" +
				"Connection: keep-alive\r\n" +
				"Content-Type: application/json\r\n" +
				"charset: \"utf-8\"\r\n" +
				"Content-Length: " + len + "\r\n" +
				"\r\n" +
				data;

		//System.out.println(msg);

		// String ���� msg �� ����Ʈ�� �ٲپ� �����ϵ��� �Ѵ�.
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

		// �����Ѵ�.
		String temp = "";
		temp = session.Receive(3000);
		// ���ڿ� ���� ����
		m_Recv = temp.trim();

		//System.out.println(m_Recv);

		session.Disconnect();

		return 0;
	}

	/**
	 *	@brief							�ֱٿ� ���� ���� ���� �ڵ带 ����
	 *	@author							������
	 *	@param							None
	 *	@return							�ֱٿ� ���� ���� ���� �ڵ�
	 */
	public int GetLastErrorCode()
	{
		int errcode = 0;
		String temp = "";
		String keyword = "errcode\": ";
		// ���ŵ� �޽����� �����޽��� �κ��� ���� ��� �Ʒ��� ���� ǥ���ȴ�.
		// "errcode": 917509, "errmessage": ...

		if (m_Recv == null)
		{
			errcode = -1;
			return errcode;
		}
		// errmessage: " �� �����ϴ� �κ� ������ ���������� ��´�.
		int start_idx = m_Recv.indexOf(keyword) + keyword.length();
		// ���� ���������� , �� ������ �κ��� �������� ��´�.
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
	 *	@brief							�ֱٿ� ���� ���� �޽����� �����޽����� ����
	 *	@author							������
	 *	@param							None
	 *	@return							�ֱٿ� ���� ���� �޽���
	 */
	public String GetLastErrorMsg()
	{
		String temp = "";
		String keyword = "errmessage\": \"";
		// ���ŵ� �޽����� �����޽��� �κ��� ���� ��� �Ʒ��� ���� ǥ���ȴ�.
		// "errmessage": "aaa"

		if (m_Recv == null)
		{
			temp = "ERROR_INVALID_HANDLE";
			return temp;
		}
		// errmessage: " �� �����ϴ� �κ� ������ ���������� ��´�.
		int start_idx = m_Recv.indexOf(keyword) + keyword.length();
		// ���� ���������� " �� ������ �κ��� �������� ��´�.
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
	 *	@brief							xml_expression üũ�Ͽ� ���Ͱ� ��������� �����Ѵ�.(http ��Ž� xml_expression �� ���ٷ� ǥ���Ǿ�� �Ѵ�.)
	 *									xml_expression üũ�Ͽ� " �� \" �� ǥ���Ѵ�.(http ��Ž� " �� backslash quotation \" ���� ǥ�õǾ�� �Ѵ�.)
	 *	@author							������
	 *	@param			xml_expression	���� ����
	 *	@return							üũ�� xml_expression;
	 */
	private String CheckXMLExpression(String xml_expression)
	{
		// ��������
		xml_expression = xml_expression.replaceAll("\n", "");
		// " �� \" �� ����
		// replaceAll �� �Ķ���Ͱ� ���Խ��� ����Ѵ�.
		// \" �� ǥ���ѱ� ���ؼ� \\ \\ \" �� ��Ÿ����. 
		// \\\\\"  ===> \"
		xml_expression = xml_expression.replaceAll("\"", "\\\\\"");

		return xml_expression;
	}


	/**
	 *	@brief							Get ���� ��û�ϱ�
	 *	@author							������
	 *	@param			path			���� ����
	 *	@param			result			���� ���
	 *	@return							�����ϸ� 0 ����
	 */		
	public int GetData(String path, String[] result)
	{
		// ��ȣȭ �ϱ�
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
//		// ����� ������ 
//		if (temp.length() < 1)
//		{
//			result[0] = "";
//		}
//		else
//		{
//			// AES �׽�Ʈ
//			//String a = "��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n��ȣ(AES) �׽�Ʈ�Դϴ�. �� ������ ���̸� ��ȣ/��ȣȭ�� �������ΰ��Դϴ�.\n";
//			//String b = EnCode(AES_Key, AES_InitialVector, a);
//			//System.out.println(b);
//			//String c = DeCode(AES_Key, AES_InitialVector, b);
//			//System.out.println(a);
//
//
//			//��ȣ Ǯ��(��ȣȭ)
//			String DecodedStr = DeCode(Common.AES_Key, Common.AES_InitialVector, temp);
//
//			// \" �� " �� �ٲ��ش�.
//			DecodedStr = DecodedStr.replaceAll("\\\\\"", "\"");
//			//System.out.println("result: "+ str);
//			result[0] = DecodedStr;
//		}

//		return GetLastErrorCode();
		
		return 0;
	}

}

