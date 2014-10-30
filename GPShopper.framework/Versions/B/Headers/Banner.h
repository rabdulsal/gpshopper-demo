//
//  Banner.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 1/12/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


#ifndef BANNER_H
#define BANNER_H

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


enum SCBannerType
{
    SCBannerUnknown,
	SCBannerGiftGuide,
	SCBannerProduct,
	SCBannerUrl,
	SCBannerQuattro,
	SCBannerEmail,
	SCBannerMultimediaTemplate,
	SCBannerSearch,
	SCBannerSection,
	SCBannerContest,
    SCBannerPromo,
    SCBannerEvent,
    SCBannerCustom,
    SCBannerPopup,
    SCBannerNoAction
};


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


@protocol SCBanner < NSObject >

-(enum SCBannerType)bannerType;
-(uint64_t)ggid;
-(uint64_t)grpid;
-(NSString *)url;
-(NSString *)searchQuery;
-(NSString *)sectionName;
-(NSString *)scriptValue;
-(uint64_t)contestid;
-(uint64_t)eventid;

@end

#define BANNER_DATE_FORMAT @"yyyy-MM-dd HH:mm:ss"

extern NSString* const kBannerKeyScriptType;
extern NSString* const kBannerKeyScriptValue;
extern NSString* const kBannerKeyPosition;
extern NSString* const kBannerKeySupplemental;
extern NSString* const kBannerKeyLabel;
extern NSString* const kBannerKeyBannerID;
extern NSString* const kBannerKeyEndDate;
extern NSString* const kBannerKeyChildBanners;
extern NSString* const kBannerKeyChildWidth;
extern NSString* const kBannerKeyChildHeight;
extern NSString* const kBannerKeyChildX;
extern NSString* const kBannerKeyChildY;

extern NSString* const kBannerTypeNameGiftGuide;
extern NSString* const kBannerTypeNameProduct;
extern NSString* const kBannerTypeNameUrl;
extern NSString* const kBannerTypeNameMultimediaTemplate;
extern NSString* const kBannerTypeNameSearch;
extern NSString* const kBannerTypeNameSection;
extern NSString* const kBannerTypeNameContest;
extern NSString* const kBannerTypeNamePromo;
extern NSString* const kBannerTypeNameEvent;
extern NSString* const kBannerTypeNameCustom;
extern NSString* const kBannerTypeNamePopup;
extern NSString* const kBannerTypeNameNoAction;

NSString* scBannerStringFromDate(NSDate *d);
NSDate* scBannerDateFromString(NSString *s);

@interface Banner : NSObject < NSCoding, SCBanner >
{
    @protected
    uint64_t bannerID;
    NSString *scriptType;
    NSString *scriptValue;
    NSString *positionName;
    NSString *bannerName;
    NSDate *endDate;
    NSArray *childBanners;
    NSDictionary *supplemental;
}

@property (readonly) enum SCBannerType bannerType;
@property (readonly) uint64_t bannerID;
@property (readonly) NSString *positionName;
@property (readonly) NSString *bannerName;
@property (readonly) NSString *scriptValue;
@property (readonly) NSDate *endDate;
@property (readonly) NSArray *childBanners;
@property (readonly) NSDictionary *supplemental;
@property (copy) NSString *md5;

-(id)initWithDict: (NSDictionary *)dict;

-(id)initWithBannerid: (uint64_t)bid
                 type: (enum SCBannerType)t
         positionName: (NSString *)pn
                label: (NSString *)l
              endDate: (NSDate *)d
          scriptValue: (NSString *)sv
         childBanners: (NSArray *)cbs;

-(NSDictionary *)attributes;

+(NSString *)nameForType: (enum SCBannerType)t;
+(NSString *)scriptValueFromBanner: (id<SCBanner>)b;
+(Banner *)newFromDictionary: (NSDictionary *)kv;

@end


@interface SCChildBanner : NSObject < NSCoding, SCBanner >
{
@protected
    NSString *scriptValue;
    CGRect normalizedFrame;
}

@property (readonly) enum SCBannerType bannerType;
@property (readonly) NSString *scriptValue;
@property (readonly) CGRect normalizedFrame;

-(id)initWithBannerType: (enum SCBannerType)t
            scriptValue: (NSString *)sv
        normalizedFrame: (CGRect)r;

+(SCChildBanner *)newFromDictionary: (NSDictionary *)kv;

@end


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------


@class SCCache;

#define kDefaultBannerManagerTimeout 600

@interface BannerManager : NSObject
{}

+(void)setRequestUrl: (NSString *)url;
+(void)setImageCachingEnabled: (BOOL)ice;

/**
 *  Defines how long before Banners are considered 'stale' and need to be refetched/refreshed.
 *  Default value is kDefaultBannerManagerTimeout.
 *
 *  @param seconds Number of seconds after which Banner is considered 'stale'
 */
+(void)setDataTimeout: (double)seconds;

+(void)setDataTimeoutEnabled: (BOOL)enabled;

+(NSArray *)bannersForPositionName: (NSString *)n;

+(Banner *)bannerForID: (uint64_t)bannerid;
+(Banner *)randomBannerForName: (NSString *)n;
+(Banner *)nthBanner: (NSUInteger)i
			 forName: (NSString *)n;
+(NSUInteger)numBannersForName: (NSString *)n;
+(uint64_t)numBanners;
+(void)refetchAll;
+(void)refetchBannersForName: (NSString *)n;

+(SCCache *)cache;

@end

#endif
