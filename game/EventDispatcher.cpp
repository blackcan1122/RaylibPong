#include "EventDispatcher.hpp"

void EventDispatcher::AddListener(const std::string& EventName, EventCallback Callback)
{
	/*
	* 
	* Speichern (Falls noch nicht existiert) den Name des Events als Key in eine Map
	* und weisen diesem Key dann eine X Anzahl an Funktionen zu die ausgef�hrt werden m�ssen
	* wenn wir es dispatchen
	* 
	*/
	m_Listener[EventName].push_back(Callback);
}

void EventDispatcher::Dispatch(std::shared_ptr<Event> EventToDispatch)
{
	// Holen uns den Name des Events
	const auto& eventName = EventToDispatch->GetName();

	// wir schauen ob sich eine Funktion, lambda etc. schon f�r das event Interessiert
	if (m_Listener.find(eventName) != m_Listener.end())
	{
		// Falls sich jemand f�r das Event Interessiert
		// Dann Loopen wir durch alle Funktionen die sich f�r das Event Interessieren
		for (const auto& listener : m_Listener[eventName])
		{
			listener(EventToDispatch);
		}
	}
}
