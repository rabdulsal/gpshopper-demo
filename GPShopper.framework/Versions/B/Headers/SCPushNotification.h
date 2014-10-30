//
//  SCPushNotification.h
//  bebe
//
//  Created by donny on 9/11/12.
//
//

#import <Foundation/Foundation.h>
#import "Banner.h"
#import "BannerView.h"
#import "SCWebTracking.h"

extern NSString* const kSCPushNotificationAPIKeyScriptType;
extern NSString* const kSCPushNotificationAPIKeyScriptValue;
extern NSString* const kSCPushNotificationAPIKeyMessageText;
extern NSString* const kSCPushNotificationAPIKeyMessageTitle;
extern NSString* const kSCPushNotificationAPIKeyMessageID;
extern NSString* const kSCPushNotificationAPIKeyMessageDate;
extern NSString* const kSCPushNotificationAPIKeyMessageType;

extern NSString* const kSCPushNotificationAPIDateFormat;

extern NSString* const kSCPushNotificationAPNSKeyScriptType;
extern NSString* const kSCPushNotificationAPNSKeyScriptValue;

extern NSString* const kSCPushNotificationMessageTypeNameBlast;
extern NSString* const kSCPushNotificationMessageTypeNameGeofence;
extern NSString* const kSCPushNotificationMessageTypeNameProductAlert;

enum SCPushNotificationMessageType
{
    SCPushNotificationMessageTypeUnknown,
    SCPushNotificationMessageTypeBlast,
    SCPushNotificationMessageTypeGeofence,
    SCPushNotificationMessageTypeProductAlert
};

NSString* nameForPushNotificationMessageType(enum SCPushNotificationMessageType t);
enum SCPushNotificationMessageType pushNotificationMessageTypeFromName(NSString *n);


@protocol PushNotificationDelegate < BannerActionDelegate >
-(void)pushNotificationGotoHomePage;
@end


/**
 Encapsulates incoming push notification data.

 In addition to a text message to display,
 SCPushNotification includes the same type / value pair as banners.

 Push notifications from GPShopper are intended to do
 whatever banners can do: redirect to a product, a web page, and so on.
 To this end, SCPushNotification includes variables scriptType and scriptValue,
 which take the same values as the corresponding variables in Banner.

 SCPushNotification also includes some bookkeeping variables
 about the message delivered: messageId, messageDate, and messageType.
 */
@interface SCPushNotification : NSObject < SCBanner >

/**
 Identifier of this message in the GPShopper data system.
 Used for tracking and analytics.
 */
@property (readonly) NSString *messageId;

/**
 Text message to display to the user.
 */
@property (readonly) NSString *message;

/**
 The title of the message.
 
 NOTE:  Due to implementation constraints, this value is _not_ present in messages arriving from APNS.
 Instead, 'message' will contain _both_ message text and title.
 */
@property (readonly) NSString *messageTitle;

/**
 When the message was sent (or otherwise made public).
 */
@property (readonly) NSDate *messageDate;

/**
 The context in which the message was sent, specifically:

  * a 'blast' to many users
  * user entered a geofence
  * price / stock alerts

 and potentially others to be added in the future.
 */
@property (readonly) enum SCPushNotificationMessageType messageType;
@property (readonly) enum SCBannerType bannerType;
@property (readonly) NSString *scriptType;
@property (readonly) NSString *scriptValue;

@property (readwrite) uint64_t ggid;
@property (readwrite) uint64_t grpid;
@property (copy) NSString *url;
@property (copy) NSString *searchQuery;
@property (copy) NSString *sectionName;
@property (readwrite) uint64_t contestid;
@property (readwrite) uint64_t eventid;

/** Constructor */
-(id)initWithMessageId: (NSString *)mi
               message: (NSString *)m
          messageTitle: (NSString *)mtl
           messageDate: (NSDate *)md
           messageType: (enum SCPushNotificationMessageType)mtp
            scriptType: (NSString *)st
           scriptValue: (NSString *)sv;

-(id)initWithMessageId: (NSString *)mi
               message: (NSString *)m
           messageDate: (NSDate *)md
           messageType: (enum SCPushNotificationMessageType)mt
            scriptType: (NSString *)st
           scriptValue: (NSString *)sv  __attribute__((deprecated));

-(id)initWithMessageId: (NSString *)mi
               message: (NSString *)m
            scriptType: (NSString *)st
           scriptValue: (NSString *)sv  __attribute__((deprecated));

/**
 A tracking event which indicates this push notification was *received*.
 */
-(SCWebTrackingEvent *)trackingEvent;

-(BOOL)actionDataIsValid;

/**
 Using the provided delegate, perform the action specified
 by the notification's script type and value.

 This is analogous to clicking on a banner.
 */
-(void)performActionWithDelegate: (id<PushNotificationDelegate>)d;

+(SCPushNotification *)newFromDictionary: (NSDictionary *)d  __attribute__((deprecated));

/**
 Factory method for use in the following UIApplicationDelegate methods:

  * application:didReceiveLocalNotification:
  * application:didReceiveRemoteNotification:

 and other similar methods.
 */
+(SCPushNotification *)newFromAPNSDictionary: (NSDictionary *)kv;

/**
 Factory method for parsing responses from the GPShopper API.
 */
+(SCPushNotification *)newFromAPIDictionary: (NSDictionary *)kv;

+(SCPushNotification *)defaultPushNotification;

+(NSDateFormatter *)dateFormatter;

@end


