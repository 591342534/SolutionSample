#ifndef WORKPLAN_PROJECT_SERVER_H_
#define WORKPLAN_PROJECT_SERVER_H_

#include <iostream>
#include <string>
#include <string.h>
#include "Mutex.h"
#include "Thread.h"
#include "ClientSession.h"
#include "NetworkLibrary.h"

namespace itstation 
{
	class CProjectServer
		: public common::Thread
	{ 
	public: 
		static CProjectServer * GetInstance();

		void initialize();

		void startServer();
		void stopServer();

		void SendMessages( int type, session_ptr ptrSocket, const char* stream, TCP_MSG_HEAD &header );

		//Implement Thread "run" interface
		virtual void OnRun();

	private: 
		CProjectServer();
		virtual ~CProjectServer();
		//ʹ�಻�ɸ���
		CProjectServer(const CProjectServer &);
		CProjectServer& operator = (const CProjectServer &);

		class CGarbo //����Ψһ��������������������ɾ��CProjectServer��ʵ�� 
		{ 
		public: 
			CGarbo() 
			{ 
			} 
			~CGarbo() 
			{ 
				if(CProjectServer::m_pInstance) 
				{
					delete CProjectServer::m_pInstance;
				}
			} 
		}; 
		static CGarbo Garbo; //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������

		static CProjectServer *m_pInstance;
		static common::Mutex m_mutex;

		bool m_status;

		//config_file_path path
		std::string config_file_path;
		
		ITcpMessageNotify *m_ptrNotify;
		ITcpServer *m_TcpServer;
		ITcpClient *m_TcpClient;
	}; 

}
#endif
