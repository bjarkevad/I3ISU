#include <osapi/Message.hpp>
#include <osapi/Utility.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/ScopedLock.hpp>
#include <vector>

namespace details
{
	class SubscriberId
	{
		public:
			void send(osapi::Message* m) const;
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
			osapi::ScopedLock lock(m_);
			SubscriberIdMap::const_iterator iter = sm_.find(msgId);
			if(iter != sm_.end())
			{
				SubscriberIdContainer& subList = iter->second;

				for( SubscriberIdContainer::const_iterator iterSubs = subList.begin() ;
						iterSubs != subList.end() ; ++iterSubs )
				{
					M *tmp = new M(*m);
					iterSubs->send(tmp);
				}
				
			}
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
