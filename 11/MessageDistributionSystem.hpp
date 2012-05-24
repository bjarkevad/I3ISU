#include <osapi/Message.hpp>
#include <osapi/Utility.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/ScopedLock.hpp>
#include <vector>
#include <map>
#include <iostream>

namespace details
{
	class SubscriberId
	{
		public:
			SubscriberId(osapi::MsgQueue* mq, unsigned long id) :
				mq_(mq), id_(id) {}

			void send(osapi::Message* m) const
			{
					mq_->send(id_, m);
			}

			bool operator==(const SubscriberId& other) const
			{
				return (mq_ == other.mq_) && (id_ == other.id_);
			}

		private:
			osapi::MsgQueue* mq_;
			unsigned long id_;
	};
}

class	MessageDistributionSystem : osapi::Notcopyable
{
	public:
		void subscribe(const std::string& msgId,
										osapi::MsgQueue* mq,
										unsigned long id);
		void unSubscribe(const std::string& msgId,
											osapi::MsgQueue* mq,
											unsigned long id);

		template<typename M>
		void notify(const std::string& msgId, M* m) const
		{
			//Lock added in updated exercise
			osapi::ScopedLock lock(m_);
			SubscriberIdMap::const_iterator iter = sm_.find(msgId);
			if(iter != sm_.end())
			{
				SubscriberIdContainer subList = iter->second;

				for( SubscriberIdContainer::const_iterator iterSubs = subList.begin() ;
						iterSubs != subList.end() ; ++iterSubs )
				{
				// We do not know who owns the original message 'm', so make a dynamically allocated copy that
				// we own. This ensures that the message is not deleted before receivers have a chance to do anything
					M *tmp = new M(*m); 
					iterSubs->send(tmp);
					std::cout << "Notified a subscriber.." << std::endl;
				}
				
			}
			//Receivers have their own copy, now it's safe to delete ours.
			//This approach is used because we do not know when subscribers are finished with the message
			//so each subscriber takes care of their own memory management. This could be improved with shared_pointers!
			delete m;
		}
		//Singleton
		static MessageDistributionSystem& getInstance()
		{
			static MessageDistributionSystem mds;
			return mds;
		}
	private:
		MessageDistributionSystem(){}

		typedef std::vector<details::SubscriberId> 						SubscriberIdContainer;
		typedef std::map<std::string, SubscriberIdContainer> 	SubscriberIdMap;
		typedef std::pair<SubscriberIdMap::iterator, bool> 		InsertResult;

		SubscriberIdMap				sm_;
		mutable osapi::Mutex	m_;
};

class SubscriberHelper : osapi::Notcopyable
{
	public:
		SubscriberHelper(const std::string& msgId,
											osapi::MsgQueue* mq,
											unsigned long id) :
										msgId_(msgId), mq_(mq), id_(id) 
	{
		MessageDistributionSystem::getInstance().subscribe(msgId_, mq_, id_);
	}

	void unsubscribe()
	{
		MessageDistributionSystem::getInstance().unSubscribe(msgId_, mq_, id_);
	}

	~SubscriberHelper()
	{
		unsubscribe();
	}

	private:
		const std::string 	msgId_;
		osapi::MsgQueue* 		mq_;
		unsigned long				id_;
};
