#include    "MessageDistributionSystem.hpp"

void MessageDistributionSystem::subscribe(const std::string& msgId,	osapi::MsgQueue* mq, unsigned long id)
{
	osapi::ScopedLock lock(m_);
	//map::insert returns a pair. 
	//The first element is the iterator to the newly inserted item
	//The second element is wether or not the insert was succesful
	//(A map containers do not allow duplicates)
	InsertResult ir = sm_.insert(std::make_pair(msgId, SubscriberIdContainer()));

	//return if the insertion was not successfull
	if(!(ir.second))
		return;

	SubscriberIdContainer& s1 = ir.first->second;

	details::SubscriberId s(mq, id);

	SubscriberIdContainer::iterator iter = find(s1.begin(), s1.end(), s);
	if(iter == s1.end())
		s1.push_back(s);
}

void MessageDistributionSystem::unSubscribe(const std::string& msgId, osapi::MsgQueue* mq, unsigned long id)
{
	osapi::ScopedLock lock(m_);
	//Search for message ID
	std::cout << "unsubscribe called, searching for: " << msgId << std::endl;
	SubscriberIdMap::iterator iter = sm_.find(msgId);
	
	//If we did not reach the end of the of the container, meaning that we found something.
	//It is possible to iterate again, but this should be pointless, since we are only able to subscribe once.
	if(iter != sm_.end())
	{
		std::cout << "Found message ID.." << std::endl;
		//Get the associated SubscriberIdContainer (the second item in the list).
		SubscriberIdContainer& subList = iter->second;
		//Temp SubscriberId used for comparison
		details::SubscriberId s(mq, id);
		//Find any members with the subscriber id "s"
		SubscriberIdContainer::iterator idIter = find(subList.begin(), subList.end(), s);
		//If we found any matches..
		if(idIter != subList.end())
		{
			//..delete it
			subList.erase(idIter);	
			std::cout << "Deleted something..!" << std::endl;
		}
	}
}
