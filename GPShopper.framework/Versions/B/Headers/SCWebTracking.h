//
//  SCWebTracking.h
//  feature
//
//  Created by kimberly on 7/10/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#ifndef SCWEBTRACKING_H
#define SCWEBTRACKING_H

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


/**
 ### Feature description ###
 
 To measure engagement across all users, apps send tracking events
 to the frontends, where they are aggregated and recorded.
 
 This data is visible in tracking console, currently at
 http://analytics.gpshopper.com/piwik/piwik/index.php
 
 For a full specificatio of tracking details, search for 'metrics' in Confluence
 or see this page in particular:
 http://utility1.gpshopper.com:8090/pages/viewpage.action?pageId=1016760
 
 (links valid as of July 2013, may be broken subsequently.)
 
 
 ### Creating ###
 
 Although a tracking event may be constructed from scratch,
 there are several factory methods for common events:
 
     // User visited Home tab.
     [SCWebTrackingEvent sectionTrackingEventWithName: @"Home"
                                               action: nil];
 
     // User logged out while in More tab.
     [SCWebTrackingEvent sectionTrackingEventWithName: @"More"
                                               action: @"logOut"];
 
     // User viewed product detail for grpid 1234567890
     [SCWebTrackingEvent productViewWithName: @"Colorblock Romper"
                                       grpid: 1234567890
                           retailerProductId: @"RMPR123"
                                  pdpSection: nil
                                   pdpAction: nil];
 
 ### Sending ###
 
 SCWebTrackingEvent instances can be sent to the frontends using one of several classes:
 
  * SCWebTracking (**preferred**):  facade for both of
    * SCWebTrackingEventBatchSender:  sends batches of events in background.
    * SCWebTrackingWebView:  loads webpages which use Javascript to record tracking data one event at a time.

 
 ### See also ###
 
 SCWebTrackingEventBatchSender, SCWebTrackingWebView, SCWebTracking
 */
@interface SCWebTrackingEvent : NSObject < NSCoding >

/**
 The event type.  Examples: browse, scan, productView, section
 */
@property (copy) NSString *type;

/**
 Date at which this event was created.
 */
@property (readonly) NSDate *date;

@property (copy) NSString *usid;

/**
 Using a pre-defined key mapping, write the contents of this event
 into a target dictionary.
 */
-(void)addToDictionary: (NSMutableDictionary *)d
encodeContainersAsJSON: (BOOL)e;

/** @name Search */

/**
 The query of this particular search.
 
 Example:  "+cat_123", "coat"
 */
@property (copy) NSString *query;

/**
 The number of results returned from this search.
 */
@property (readwrite) int numResult;

/** @name Product view */

/**
 Name of the product.  Example: "Enbroidered Logo Colorblock Romper"
 */
@property (copy) NSString *productName;

/**
 Retailer's id for the product.  Example: RMPR123
 */
@property (copy) NSString *retailerProductId;

/**
 GRPID of the product.
 */
@property (readwrite) uint64_t grpid;

/**
 Name of a particular section on product detail page.  Example:  Reviews, Find at Store
 */
@property (copy) NSString *pdpSection;

/**
 Name of an action taken by the user on product detail page.  Example:  Share by Email
 */
@property (copy) NSString *pdpAction;

@property (copy)NSString *browse;
@property (copy) NSString *productId;
@property (readwrite) int quantity;
@property (copy) NSArray *products;
@property (copy) NSString *productEventType;

/* List */
@property (copy) NSString *listType;
@property (copy) NSString *listAction;
@property (copy) NSString *listId;
@property (retain) NSArray *listProductNames;
@property (retain) NSArray *listPiIds;
@property (retain) NSArray *listGrpIds;
@property (retain) NSArray *listRpIds;

/** @name Banners and push notifications */

/**
 The script type of a banner / push notification.
 */
@property (copy) NSString *scriptType;

/**
 The script value of a banner / push notification.
 */
@property (copy) NSString *scriptValue;

/**
 Message id (?) for a push notification.
 */
@property (copy) NSString *pnId;

/**
 Title of a push notification.
 */
@property (copy) NSString *pnTitle;

/**
 Banner position (ex. 'home_left')
 */
@property (copy) NSString *bannerPosition;

/**
 Banner id.  Corresponds to key on admin.BannerManagement
 */
@property (copy) NSString *bannerId;

/**
 Banner name/label
 */
@property (copy) NSString *bannerName;

/** @name Sections */

/**
 Path of the current section, including one or more section names.
 Example: [More, Privacy Policy]
 */
@property (retain) NSArray *sectionNames;

/**
 The action occuring in the section, including multiple levels of detail.
 Example: [Registration, Success]
 */
@property (retain) NSArray *sectionActions;

/**
 Set a global, visitor ID.  Note that setting a visitor ID re-sets
 the Visit Count to 0.
 */
+(void)setVisitorID: (NSString *)vid;

/**
 Local instance of visitor ID.
 */
@property (copy) NSString *visitorId;

/**
 Increment the Visit Count by 1.  Note that the Visit Count is re-set
 to 0 every time that a new VisitorID is set.
 */
+(void)incrementVisitCount;

/**
 Local instance of the visitor count.
 */
@property (assign) uint visitCount;

/**
 Per-instance copy of globals at time of instance creation.
 */
@property (readonly) NSDictionary *globalsSnapshot;

-(void)postNotification;

+(NSDateFormatter *)dateFormatter;

/** @name Custom values */

/**
 Any custom data that does not match one of SCWebTrackingEvent's properties.
 
 Example: { "loyalty_tier": "silver" }
 */
@property (retain) NSDictionary *customArgs;

/**
 Sets global values.  Intended for app-wide data like language, profile id, etc.
 */
+(void)setGlobalValue: (NSString *)v
               forKey: (NSString *)k;

/** @name Factory methods */

+(SCWebTrackingEvent *)browseTrackingEventForPath: (NSString *)p;
+(SCWebTrackingEvent *)browseTrackingEventForPath: (NSString *)p
                                       numResults: (int)n;
+(SCWebTrackingEvent *)searchTrackingEventForQuery: (NSString *)q
                                        numResults: (int)n;

/**
 Creates an event for SDK data tracking
 */
+(SCWebTrackingEvent *)sdkTrackingEventWithAction:(NSString *)action;

/**
 Creates an event for a section.
 */
+(SCWebTrackingEvent *)sectionTrackingEventWithNames: (NSArray *)ns
                                             actions: (NSArray *)as;
+(SCWebTrackingEvent *)sectionTrackingEventWithName: (NSString *)n
                                             action: (NSString *)a;

/**
 Creates an event for a banner click.
 
 Suggested use:
 inside implementation of BannerActionDelegate :: bannerView:willPerformActionForBanner:
 */
+(SCWebTrackingEvent *)bannerTrackingEventWithPosition: (NSString *)p
                                              bannerId: (NSString *)i
                                            scriptType: (NSString *)st
                                           scriptValue: (NSString *)sv;
+(SCWebTrackingEvent *)bannerTrackingEventWithPosition: (NSString *)p
                                              bannerId: (NSString *)i
                                            bannerName: (NSString *)n
                                            scriptType: (NSString *)st
                                           scriptValue: (NSString *)sv;
+(SCWebTrackingEvent *)productEventWithEventType: (NSString *)t
                                       productId: (NSString *)i;

/**
 Creates an event for an event on the product detail page.
 */
+(SCWebTrackingEvent *)productViewWithName: (NSString *)n
                                     grpid: (uint64_t)g
                         retailerProductId: (NSString *)rpid
                                pdpSection: (NSString *)s
                                 pdpAction: (NSString *)a;

/**
 Creates an event for a list action.
 */
+ (SCWebTrackingEvent *)listEventWithType:(NSString *)type
                                   action:(NSString *)action
                                     slId:(NSString *)slId
                             productNames:(NSArray *)productNames
                                    piIds:(NSArray *)piIds
                                   grpIds:(NSArray *)grpIds
                                    rpIds:(NSArray *)rpIds;

@end


@protocol SCWebTrackingEventSender < NSObject >

@required
-(void)sendTrackingEvent: (SCWebTrackingEvent *)e;

@optional
-(void)sendTrackingEvents: (NSArray *)es;

@end


#define kSCWebTrackingDefaultFilename @"scwebtracking_default"

/**
 A facade class that enqueues and sends tracking events.

 Example usage:

 SCWebTrackingEvent *e=[SCWebTrackingEvent searchTrackingEventForQuery: @"hdtv" numResults: 23];
 [SCWebTracking sendTrackingEvent: e];


 ### Queueing ###

 Events are sent in a first-in, first-out order.
 An event will be sent immediately unless:

 * send is disabled
 * there are prior events in the queue


 ### Archiving ###

 On leaving foreground, unsent events are archived.
 The recorded events can be sent later, after returning to foreground
 or restarting the app.


 ### Sending ###

 SCWebTracking can send events using either
 SCWebTrackingEventBatchSender or SCWebTrackingWebView.

 By default, events are sent in batches.  To use SCWebTrackingWebView instead,
 use setWebView:


 ### See also ###

 SCWebTrackingEvent, SCWebTrackingEventBatchSender, SCWebTrackingWebView
 */
@interface SCWebTracking : NSObject < NSCoding >
{
    NSMutableArray *eventQueue;
    NSMutableArray *senders;
    uint batchSize;
}

@property (readwrite, nonatomic) BOOL enabled;
@property (readonly) NSString *archiveFilename;
@property (readwrite) uint batchSize;

-(void)setWebView: (id)wv  __attribute__((deprecated));
-(void)sendTrackingEvent: (SCWebTrackingEvent *)e;
-(void)scheduleArchiveOnCloseWithFilename: (NSString *)fn;

-(NSArray *)trackingEventSenders;
-(void)addTrackingEventSender: (id<SCWebTrackingEventSender>)s;
-(void)removeTrackingEventSender: (id<SCWebTrackingEventSender>)s;

+(SCWebTracking *)defaultInstance;

+(void)setWebView: (id)wv  __attribute__((deprecated));

/**
 Enables / disables sending.  While disabled, events will still be added to the queue.
 When re-enabled, send will begin with the events added first.
 */
+(void)setEnabled: (BOOL)e;

/**
 Sets the size of event batches.  Applies only to batched (non-webview) sending.
 */
+(void)setBatchSize: (uint)b;

/**
 Add a tracking event to be sent.
 */
+(void)sendTrackingEvent: (SCWebTrackingEvent *)e;

+(NSArray *)trackingEventSenders;

+(void)addTrackingEventSender: (id<SCWebTrackingEventSender>)s;

+(void)removeTrackingEventSender: (id<SCWebTrackingEventSender>)s;

@end


@class SCWebTrackingEventBatchSender;

/**
 Event callbacks from SCWebTrackingEventBatchSender.
 */
@protocol SCWebTrackingEventBatchSenderListener

/**
 Called when sender completes a remote call.
 No guarantees are made as to whether events were recorded successfully,
 only that the round trip has been completed.
 
 @param s  The sender in question
 
 @param es The events sent.
 */
-(void)scWebTrackingEventBatchSender: (SCWebTrackingEventBatchSender *)s
                          sentEvents: (NSArray *)es;

@end


/**
 Sends multiple instances of SCWebTrackingEvent in one remote call.
 
 ### See also ###
 
 SCWebTrackingEvent, SCWebTracking
 */
@interface SCWebTrackingEventBatchSender : NSObject < SCWebTrackingEventSender >
{
    NSMutableDictionary *batches;
    SCObjectRetriever *retriever;
}

/**
 Listener to be notified on send completion.
 */
@property (assign) id<SCWebTrackingEventBatchSenderListener> listener;

/**
 Sends events together in one request.
 
 @param es  The events to send.
 */
-(void)sendEvents: (NSArray *)es;

/**
 The remote url to which requests are sent.
 
 Url should support the GPShopper mobile API, and will typically be of the form
 http://something.gpshopper.com/mobile, the "/mobile" at the end being the important part.
 */
+(NSString *)requestUrl;

/**
 Set the request url.
 */
+(void)setRequestUrl: (NSString *)s;

@end

#endif
