package com.innovion_inc;

import com.google.gdata.client.Query;
import com.google.gdata.client.calendar.CalendarQuery;
import com.google.gdata.client.calendar.CalendarService;
import com.google.gdata.data.DateTime;
import com.google.gdata.data.Link;
import com.google.gdata.data.PlainTextConstruct;
import com.google.gdata.data.batch.BatchOperationType;
import com.google.gdata.data.batch.BatchStatus;
import com.google.gdata.data.batch.BatchUtils;
import com.google.gdata.data.calendar.CalendarEntry;
import com.google.gdata.data.calendar.CalendarEventEntry;
import com.google.gdata.data.calendar.CalendarEventFeed;
import com.google.gdata.data.calendar.CalendarFeed;
import com.google.gdata.data.calendar.WebContent;
import com.google.gdata.data.extensions.ExtendedProperty;
import com.google.gdata.data.extensions.Recurrence;
import com.google.gdata.data.extensions.Reminder;
import com.google.gdata.data.extensions.Reminder.Method;
import com.google.gdata.data.extensions.When;
import com.google.gdata.data.extensions.Where;
import com.google.gdata.data.extensions.Who;
import com.google.gdata.util.AuthenticationException;
import com.google.gdata.util.ServiceException;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.List;
import java.util.TimeZone;

public class CalendarEventTest {
	public static void runAll()
	{
		CalendarService calendarService = new CalendarService("Innvion-TimeTracker-1.0");

		// authentication
		try
		{
			calendarService.setUserCredentials(userName, userPassword);
		}
		catch (final AuthenticationException e)
		{
			e.printStackTrace();
		}

		try
		{
			URL feedUrl = new URL(primaryCalendarFeedUrlString);  // primary calendar
			//URL feedUrl = new URL("https://www.google.com/calendar/feeds/1m2h2p91q4t8kbq4lrgs9lm03o@group.calendar.google.com/private/full");  // Time Tracker App Calendar
	        //URL feedUrl = new URL("https://www.google.com/calendar/feeds/jm0psub0j6grrbdgiukpmu82oo@group.calendar.google.com/private/full");  // Send Me App Calendar
	        //URL feedUrl = new URL("https://www.google.com/calendar/feeds/ts0gao1ncdd021pmds3a2ct010@group.calendar.google.com/private/full");  // Shared Calendar
	
			//
			System.out.println("----------* list all the calendar events");
			listCalendarEventEntries(calendarService, feedUrl);

			// calendar event query
			System.out.println("\n----------* query calendar events using full text");
			queryCalendarEventsUsingFullText(calendarService, feedUrl);
			System.out.println("\n----------* query calendar events using date range");
			queryCalendarEventsUsingDateRange(calendarService, feedUrl);
	
			// calendar events
			System.out.println("\n----------* add a single calendar event");
			CalendarEventEntry singleCalendarEvent = addSingleCalendarEvent(calendarService, feedUrl);
			CalendarEventEntry singleCalendarEvent2 = addSingleCalendarEvent2(calendarService, feedUrl);
			System.out.println("\n----------* add a quick calendar event");
			CalendarEventEntry quickCalendarEvent = addQuickCalendarEvent(calendarService, feedUrl);
			System.out.println("\n----------* add a web content calendar event");
			CalendarEventEntry webContentCalendarEvent = addWebContentCalendarEvent(calendarService, feedUrl,
					"World Cup", "image/gif", "http://www.google.com/logos/worldcup06.gif",
					"http://www.google.com/calendar/images/google-holiday.gif", "276", "120"
			);
			System.out.println("\n----------* add a recurring calendar event");
			CalendarEventEntry recurringCalendarEvent = addRecurringCalendarEvent(calendarService, feedUrl, "Tennis with Dan", "Weekly tennis lesson.");

			//
			printCalendarEventInfo(singleCalendarEvent);
			
			System.out.println("\n----------* update a calendar event's title");
			CalendarEventEntry updatedCalendarEvent = updateCalendarEventTitle(singleCalendarEvent, "Important meeting");
			System.out.println("\n----------* add a reminder to a calendar event");
			CalendarEventEntry reminderCalendarEvent = addReminderToCalendarEvent(updatedCalendarEvent, 15, Method.EMAIL);
			System.out.println("\n----------* add an extended property to a calendar event");
			CalendarEventEntry extentedPropertyCalendarEvent = addExtendedPropertyToCalendarEvent(reminderCalendarEvent);

			printCalendarEventInfo(extentedPropertyCalendarEvent);
				
			//System.out.println("\ttest 1: event IDs are " + (eventId1.equals(eventId2) ? "equal" : "not equal"));
			//System.out.println("\ttest 1: iCal UIDs are " + (iCalUID1.equals(iCalUID2) ? "equal" : "not equal"));
			//System.out.println("\ttest 1: sequence numbers are " + (sequenceNo1 == sequenceNo2 ? (0 == sequenceNo1 ? "not assigned" : "equal") : "not equal"));

			//
			// set whether the event needs to be synced i.e., the iCal UID and Sequence number need to be honored
			printCalendarEventInfo(singleCalendarEvent2);
			
			System.out.println("\n----------* set a sync property to a calendar event");
			CalendarEventEntry syncPropertyCalendarEvent = setSyncPropertyToCalendarEvent(singleCalendarEvent2);
	
			printCalendarEventInfo(syncPropertyCalendarEvent);

			//System.out.println("\ttest 2: event IDs are " + (eventId1.equals(eventId2) ? "equal" : "not equal"));
			//System.out.println("\ttest 2: iCal UIDs are " + (iCalUID1.equals(iCalUID2) ? "equal" : "not equal"));
			//System.out.println("\ttest 2: sequence numbers are " + (sequenceNo1 == sequenceNo2 ? (0 == sequenceNo1 ? "not assigned" : "equal") : "not equal"));
		
			//
			System.out.println("\n----------* delete all the calendar events");
			List<CalendarEventEntry> eventsToDelete = new ArrayList<CalendarEventEntry>();
			eventsToDelete.add(singleCalendarEvent);  // error: invalid identifier
			eventsToDelete.add(singleCalendarEvent2);  // error: invalid identifier
			eventsToDelete.add(extentedPropertyCalendarEvent);  // OK
			eventsToDelete.add(syncPropertyCalendarEvent);  // OK
			eventsToDelete.add(quickCalendarEvent);
			eventsToDelete.add(webContentCalendarEvent);
			eventsToDelete.add(recurringCalendarEvent);

			deleteCalendarEvents(calendarService, feedUrl, eventsToDelete);
			
			// ???
			String userId = "innovion.inc@gmail.com";
			System.out.println("\n----------* list attendee's status");
			List<String> eventIds = listAttendeeStatus(calendarService, userId);
			System.out.println("\n----------* update attendee's status");
			int i = 0;
			for (String eventId : eventIds)
			{
				if (i % 3 == 0)
					updateAttendeeStatus(calendarService, userId, eventId, Who.AttendeeStatus.EVENT_ACCEPTED);
				else if (i % 3 == 1)
					updateAttendeeStatus(calendarService, userId, eventId, Who.AttendeeStatus.EVENT_DECLINED);
				else
					updateAttendeeStatus(calendarService, userId, eventId, Who.AttendeeStatus.EVENT_TENTATIVE);
				++i;
			}
		}
		catch (final MalformedURLException e)
		{
			e.printStackTrace();
		}
	}

	// list calendar's event entries
	private static void listCalendarEventEntries(CalendarService calendarService, URL feedUrl)
	{
		try
		{
			CalendarFeed resultFeed = calendarService.getFeed(feedUrl, CalendarFeed.class);

			System.out.println("My calendar's event entries:");
	        for (CalendarEntry entry : resultFeed.getEntries())
	        {
	        	System.out.println("\t" + entry.getTitle().getPlainText());
	        }
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
	}
	
	// query calendar event entries
	private static void queryCalendarEventsUsingFullText(CalendarService calendarService, URL feedUrl)
	{
		try
		{
	        Query query = new Query(feedUrl);
	        query.setFullTextQuery("test");
	            
	        // send the request with the built query URL
	        CalendarEventFeed resultFeed = calendarService.query(query, CalendarEventFeed.class);

	        // take the first match and print the title
	        System.out.println("Events matching " + query + ":");
	        for (CalendarEventEntry matchEntry : resultFeed.getEntries())
	        {
	            System.out.println("\t" + matchEntry.getTitle().getPlainText());
	        }
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
	}

	// query calendar event entries
	private static void queryCalendarEventsUsingDateRange(CalendarService calendarService, URL feedUrl)
	{
		try
		{
			// XSD data types: date and time
//			/DateTime now = DateTime.now();
	        DateTime startTime = DateTime.parseDate("2010-10-14");
	        DateTime endTime = DateTime.parseDate("2010-10-20");  // 2010-10-20 00:00:00
	        //DateTime endTime = DateTime.parseDateTime("2010-10-20T23:00:00");  // 2010-10-20 23:00:00
	        //DateTime endTime = DateTime.parseDateTime("2010-10-20T23:00:00+09:00");
	            
	        CalendarQuery query = new CalendarQuery(feedUrl);
	        query.setMinimumStartTime(startTime);
	        query.setMaximumStartTime(endTime);

	        // send the request with the built query URL
	        CalendarEventFeed resultFeed = calendarService.query(query, CalendarEventFeed.class);

	        // take the first match and print the title
	        System.out.println("Events from " + startTime.toString() + " to " + endTime.toString() + ":");
	        for (CalendarEventEntry matchEntry : resultFeed.getEntries())
	        {
	            System.out.println("\t" + matchEntry.getTitle().getPlainText());
	        }
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
	}

	// add a calendar event
	private static CalendarEventEntry addSingleCalendarEvent(CalendarService calendarService, URL feedUrl)
	{
		try
		{
	        String eventTitle = "Pi Day Party";
			String eventContent = "I am throwing a Pi Day Party!";

			return addCalendarEvent(calendarService, feedUrl, eventTitle, eventContent, null, null, null, false, null);
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	// add a calendar event
	private static CalendarEventEntry addSingleCalendarEvent2(CalendarService calendarService, URL feedUrl)
	{
		try
		{
	        String eventTitle = "Pi Day Party 2";
			String eventContent = "I am throwing a Pi Day Party 2!";

	        Calendar calendar = new GregorianCalendar();
	        DateTime startTime = new DateTime(calendar.getTime(), TimeZone.getDefault());
	        calendar.add(Calendar.MINUTE, 30);
	        DateTime endTime = new DateTime(calendar.getTime(), TimeZone.getDefault());
			//DateTime startTime = DateTime.parseDateTime("2010-10-14T15:00:00+09:00");
	        //DateTime endTime = DateTime.parseDateTime("2010-10-14T17:00:00+09:00");

	        When eventTimes = new When();
	        eventTimes.setStartTime(startTime);
	        eventTimes.setEndTime(endTime);
	        Where eventLocation = new Where(Where.Rel.EVENT, "location2-label", "location2-value");

			return addCalendarEvent(calendarService, feedUrl, eventTitle, eventContent, eventTimes, eventLocation, null, false, null);
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	// add a quick calendar event
	private static CalendarEventEntry addQuickCalendarEvent(CalendarService calendarService, URL feedUrl)
	{
		try
		{
	        String eventTitle = "Quick Event";
			String eventContent = "I am throwing a Quick Event!";

	        Calendar calendar = new GregorianCalendar();
	        DateTime startTime = new DateTime(calendar.getTime(), TimeZone.getDefault());
	        calendar.add(Calendar.MINUTE, 30);
	        DateTime endTime = new DateTime(calendar.getTime(), TimeZone.getDefault());
			//DateTime startTime = DateTime.parseDateTime("2010-10-14T15:00:00+09:00");
	        //DateTime endTime = DateTime.parseDateTime("2010-10-14T17:00:00+09:00");

	        When eventTimes = new When();
	        eventTimes.setStartTime(startTime);
	        eventTimes.setEndTime(endTime);
	        Where eventLocation = new Where(Where.Rel.EVENT, "quick event location label", "quick event location value");

			return addCalendarEvent(calendarService, feedUrl, eventTitle, eventContent, eventTimes, eventLocation, null, true, null);
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	// add a web content calendar event
	private static CalendarEventEntry addWebContentCalendarEvent(CalendarService calendarService, URL feedUrl, String title, String type, String url, String icon, String width, String height)
	{
		try
		{
			//
	        WebContent wc = new WebContent();
	        wc.setHeight(height);
	        wc.setWidth(width);
	        wc.setTitle(title);
	        wc.setType(type);
	        wc.setUrl(url);
	        wc.setIcon(icon);

	        //
	        Calendar calendar = new GregorianCalendar();
	        DateTime startTime = new DateTime(calendar.getTime(), TimeZone.getDefault());
	        calendar.add(Calendar.MINUTE, 30);
	        DateTime endTime = new DateTime(calendar.getTime(), TimeZone.getDefault());

	        When eventTimes = new When();
	        eventTimes.setStartTime(startTime);
	        eventTimes.setEndTime(endTime);

	        return addCalendarEvent(calendarService, feedUrl, title, null, eventTimes, null, null, false, wc);
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	// add a web content calendar event
	private static CalendarEventEntry addRecurringCalendarEvent(CalendarService calendarService, URL feedUrl, String eventTitle, String eventContent)
	{
		try
		{
		    //String recurData = "DTSTART;VALUE=DATE:20101001\r\n"
		    //    + "DTEND;VALUE=DATE:20101002\r\n"
		    //    + "RRULE:FREQ=WEEKLY;BYDAY=Tu,Th;UNTIL=20101031\r\n";
		    //String recurData = "DTSTART;VALUE=DATETIME:20101001T110000Z\r\n"
		    //    + "DTEND;VALUE=DATETIME:20101001T130000Z\r\n"
		    //    + "RRULE:FREQ=WEEKLY;BYDAY=Tu,Th;UNTIL=20101031\r\n";
		    String recurData = "DTSTART;VALUE=DATETIME:20101001T020000+0900\r\n"  // 11:00 am
		        + "DTEND;VALUE=DATETIME:20101001T04000+0900\r\n"  // 1:00 pm
		        + "RRULE:FREQ=WEEKLY;BYDAY=Tu,Th;UNTIL=20101031\r\n";

	        return addCalendarEvent(calendarService, feedUrl, eventTitle, eventContent, null, null, recurData, false, null);
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	private static CalendarEventEntry addCalendarEvent(CalendarService service, URL eventFeedUrl,
			String eventTitle, String eventContent, When when, Where where, String recurData,
			boolean isQuickAdd, WebContent wc) throws ServiceException, IOException
	{
		CalendarEventEntry entry = new CalendarEventEntry();

		entry.setTitle(new PlainTextConstruct(eventTitle));
		entry.setContent(new PlainTextConstruct(eventContent));
		entry.setQuickAdd(isQuickAdd);
		entry.setWebContent(wc);

		// if a recurrence was requested, add it.
		// otherwise, set the time (the current date and time) and duration (30 minutes) of the event.
		if (null == recurData)
		{
			if (null != when) entry.addTime(when);
			if (null != where) entry.addLocation(where);
		}
		else
		{
			Recurrence recur = new Recurrence();
			recur.setValue(recurData);
			entry.setRecurrence(recur);
		}

		// send the request and receive the response:
		return service.insert(eventFeedUrl, entry);
    }

	private static CalendarEventEntry updateCalendarEventTitle(CalendarEventEntry entry, String newTitle)
	{
		try
		{
		    entry.setTitle(new PlainTextConstruct(newTitle));
		    
		    return entry.update();
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}
	
	private static CalendarEventEntry addReminderToCalendarEvent(CalendarEventEntry entry, int minutes, Method methodType)
	{
		try
		{
		    Reminder reminder = new Reminder();
		    reminder.setMinutes(minutes);
		    reminder.setMethod(methodType);
		    entry.getReminder().add(reminder);
		   
		    return entry.update();
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}
	
	private static CalendarEventEntry addExtendedPropertyToCalendarEvent(CalendarEventEntry entry)
	{
		try
		{
		    ExtendedProperty property = new ExtendedProperty();
		    property.setName("http://www.example.com/schemas/2005#mycal.id");
		    property.setValue("1234");
		    entry.addExtension(property);
		   
		    return entry.update();
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}
	
	private static CalendarEventEntry setSyncPropertyToCalendarEvent(CalendarEventEntry entry)
	{
		try
		{
		    entry.setSyncEvent(true);
		   
		    return entry.update();
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	private static void deleteCalendarEvents(CalendarService service, URL eventFeedUrl, List<CalendarEventEntry> eventsToDelete)
	{
		try
		{
			// add each item in eventsToDelete to the batch request.
			CalendarEventFeed batchRequest = new CalendarEventFeed();
			for (int i = 0; i < eventsToDelete.size(); ++i)
			{
				CalendarEventEntry toDelete = eventsToDelete.get(i);
				// modify the entry toDelete with batch ID and operation type.
				BatchUtils.setBatchId(toDelete, String.valueOf(i));
				BatchUtils.setBatchOperationType(toDelete, BatchOperationType.DELETE);
				batchRequest.getEntries().add(toDelete);
			}
	
		    // get the URL to make batch requests to
		    CalendarEventFeed feed = service.getFeed(eventFeedUrl, CalendarEventFeed.class);
		    Link batchLink = feed.getLink(Link.Rel.FEED_BATCH, Link.Type.ATOM);
		    URL batchUrl = new URL(batchLink.getHref());
	
		    // submit the batch request
		    CalendarEventFeed batchResponse = service.batch(batchUrl, batchRequest);
	
		    // ensure that all the operations were successful.
		    boolean isSuccess = true;
		    for (CalendarEventEntry entry : batchResponse.getEntries())
		    {
		    	String batchId = BatchUtils.getBatchId(entry);
		    	if (!BatchUtils.isSuccess(entry))
		    	{
		    		isSuccess = false;
		    		BatchStatus status = BatchUtils.getBatchStatus(entry);
		    		System.out.println("\t" + batchId + " failed (" + status.getReason() + ") " + status.getContent());
		    	}
		    }
		    if (isSuccess)
		    	System.out.println("\tsuccessfully deleted all events via batch request.");
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
	}

	private static List<String> listAttendeeStatus(CalendarService service, String userId)
	{
		try
		{
			String eventsFeedUrl = METAFEED_URL_BASE + userId + "/private/composite";
			// partial query ??
			String fields = "entry(@gd:etag,id,title,gd:who[@email='" + userId + "'])";
			
			CalendarQuery partialQuery = new CalendarQuery(new URL(eventsFeedUrl));
			partialQuery.setFields(fields);
			DateTime startTime = DateTime.now();
			partialQuery.setMinimumStartTime(startTime);
			partialQuery.setMaximumStartTime(new DateTime(startTime.getValue() + 604800000, startTime.getTzShift()));  // 604800000 msec = 7 days

			List<String> eventIds = new ArrayList<String>();
			CalendarEventFeed eventFeed = service.query(partialQuery, CalendarEventFeed.class);
			for (CalendarEventEntry event : eventFeed.getEntries())
			{
				String eventId = event.getId().substring(event.getId().lastIndexOf("/") + 1);
				eventIds.add(eventId);
				
				String attendeeStatus = event.getParticipants().get(0).getAttendeeStatus();
				System.out.println("\t" + eventId + ": " + event.getTitle().getPlainText() + ": (" + (null != attendeeStatus ? attendeeStatus : "no status") + ")");
			}
			
			return eventIds;
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}

	private static void updateAttendeeStatus(CalendarService service, String userId, String eventId, String selection)
	{
		try
		{
			// URL of calendar entry to update.
			String eventEntryUrl = METAFEED_URL_BASE + userId + EVENT_FEED_URL_SUFFIX + eventId;
			// selection criteria to fetch only the attendee status of specified user.
			String selectAttendee = "@gd:etag,title,gd:who[@email='" + userId + "']";
			
			Query partialQuery = new Query(new URL(eventEntryUrl));
			partialQuery.setFields(selectAttendee);
			
			CalendarEventEntry event = service.getEntry(partialQuery.getUrl(), CalendarEventEntry.class);
			
			// the participant list will contain exactly one attendee matching above partial query selection criteria.
			event.getParticipants().get(0).setAttendeeStatus(selection);
			
			// field selection to update attendeeStatus only.
			String toUpdateFields = "gd:who/gd:attendeeStatus";
	
			// make patch request which returns full representation for the event.
			event = service.patch(new URL(eventEntryUrl), toUpdateFields, event);
	
			// print the updated attendee status.
			System.out.println("\t" + event.getTitle().getPlainText() + " updated to: " + event.getParticipants().get(0).getAttendeeStatus());
		}
		catch (final ServiceException e)
		{
			e.printStackTrace();
		}
		catch (final IOException e)
		{
			e.printStackTrace();
		}
	}
	
	private static void printCalendarEventInfo(CalendarEventEntry event)
	{
		String eventId = event.getId();
		//String eventId = event().substring(event().lastIndexOf("/") + 1);
		boolean isSync = event.isSyncEvent();
		String iCalUID = event.getIcalUID();
		int seqNo = event.getSequence();
		
		System.out.println("\tevent title: " + event.getTitle().getPlainText());
		System.out.println("\t\tevent ID: " + eventId);
		System.out.println("\t\tsync?: " + isSync);
		System.out.println("\t\tiCal UID: " + (null == iCalUID ? "null" : iCalUID));
		System.out.println("\t\tsequence NO: " + (event.hasSequence() ? "unassigned" : seqNo));
	}
	
	// the base URL for a user's calendar metafeed (needs a username appended).
	private static final String METAFEED_URL_BASE = "https://www.google.com/calendar/feeds/";
	// the string to add to the user's metafeedUrl to access the event feed.
	private static final String EVENT_FEED_URL_SUFFIX = "/private/full/";
	
	private static final String userName = "innovion.inc@gmail.com";
	private static final String userPassword = "innovion2gmail";

	// the URL for the primary calendar feed of the specified user.
	// (e.g. https://www.google.com/calendar/feeds/jdoe@gmail.com/private/full
    private static String primaryCalendarFeedUrlString = METAFEED_URL_BASE + userName + EVENT_FEED_URL_SUFFIX;  // primary calendar
    //private static String primaryCalendarFeedUrlString = "https://www.google.com/calendar/feeds/default/private/full";  // primary calendar
}