//
//  BannerView.h
//  Slifter_iphone_rewrite
//
//  Created by kimberly on 7/14/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SCBanner;
@class Banner;
@class SCChildBanner;
@protocol QWAdViewDelegate;
@class BannerView;
@class Logger;



enum SCBannerViewOrdering
{
    SCBannerViewOrderingRandom,
    SCBannerViewOrderingSequential,
    SCBannerViewOrderingFixed
};


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface BannerPreloader : NSObject
{}

+(void)startListening;
+(void)stopListening;
+(BOOL)listening;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@protocol BannerActionDelegate < NSObject >

@optional
-(void)bannerGotoWapPageWithUrl: (NSString *)url;
-(void)bannerGotoMailFormWithSubject: (NSString *)subject
					 receiverAddress: (NSString *)receiverAddress;
-(void)bannerGotoSectionNamed: (NSString *)name;
-(void)bannerGotoLandingPageForGrpid: (uint64_t)grpid
                        supplemental: (NSDictionary *)ss;
-(void)bannerGotoContestPageForContestid: (uint64_t)contestid;
-(void)bannerGotoGiftGuideForGgid: (uint64_t)ggid;
-(void)bannerGotoSearchResultsForQuery: (NSString *)query;
-(void)bannerGotoMultimediaTemplateForGgid: (uint64_t)ggid;
-(void)bannerGotoPromoPageForGrpid: (uint64_t)grpid;
-(void)bannerGotoEventForEventid: (uint64_t)i;
-(void)bannerGotoCustomAction: (NSString *)scriptAction;
-(void)bannerGotoPopupWithContent: (NSString *)content;

-(void)bannerView: (BannerView *)v
willPerformActionForBanner: (Banner *)b;
-(void)bannerView: (BannerView *)v
didPerformActionForBanner: (Banner *)b;

-(void)bannerView: (BannerView *)v
willPerformActionForChildBanner: (SCChildBanner *)cb
     parentBanner: (Banner *)b;
-(void)bannerView: (BannerView *)v
didPerformActionForChildBanner: (SCChildBanner *)cb
     parentBanner: (Banner *)b;

@end


//----------------------------------------------------------------
//----------------------------------------------------------------


@interface BannerView : UIView
{	
	NSMutableString *bannerName;
	uint64_t index;
	BOOL hasContent;
    uint64_t currentBannerIndex;
	
	UIActivityIndicatorView *activityView;
    NSMutableArray *childButtons;

	id<QWAdViewDelegate> qwadDelegate;
	
	NSMutableString *imageUrl;
    NSMutableString *pendingImageUrl;
    NSUInteger duplicateImageRequests;
	
    double lastReloadTime;
    BOOL displayedImage;
}

@property (assign) id<QWAdViewDelegate> qwadDelegate;
@property (readwrite) uint64_t index;
@property (readonly) BOOL hasContent;
@property (assign) NSInteger bannerViewContentMode;
@property (readwrite) enum SCBannerViewOrdering ordering;
@property (readonly) BOOL displayedImage;
@property (readonly) Banner *banner;

+(void)setActivityIndicatorViewStyle:(UIActivityIndicatorViewStyle)style;

-(void)reloadData;

-(void)setBannerName:(NSString *)bn;
-(NSString *)bannerName;
-(UIActivityIndicatorView *)activityView;

+(void)performActionForBanner: (id<SCBanner>)banner;
+(void)preloadDataForBannersAtPosition: (NSString *)pos;

+(void)setBannerActionDelegate: (id<BannerActionDelegate>)d;
+(void)setBannerFetchReactionInterval: (double)t;




@end
