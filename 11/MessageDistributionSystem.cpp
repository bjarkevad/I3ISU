#include    "MessageDistributionSystem.hpp"

void MessageDistributionSystem::subscribe(const std::string& msgId,
																					osapi::MsgQueue* mq,
																					unsigned long id)
{
	osapi::ScopedLock lock(m_);
	InsertResult ir = sm_.insert(std::make_pair(msgId,
																SubscriberIdContainer()));

	SubscriberIdContainer& s1 = ir.first->second;

	details::SubscriberId s(mq, id);

	SubscriberIdContainer::iterator iter = find(s1.begin(), s1.end(), s);
	if(iter == s1.end())
		s1.push_back(s);
}

void MessageDistributionSystem::unSubscribe(const std::string& msgId,
																						osapi::MsgQueue* mq,
																						unsigned long id)
{
	osapi::ScopedLock lock(m_);
	//Search for message ID
	SubscriberIdMap::iterator iter = sm_.find(msgId);

	//If message ID is found
	if(iter != sm_.end())
	{
		//Get the associated SubscriberIdContainer
		SubscriberIdContainer& subList = iter->second;
		//Temp SubscriberId used for comparison
		details::SubscriberId s(mq, id);
		//Find any members with the subscriber id "s"
		SubscriberIdContainer::iterator idIter = find(subList.begin(), subList.end(), s);
		//If we found any matches..
		if(idIter != subList.end())
			//..delete it
			subList.erase(idIter);	
	}
}
