//
//  SCBannerScrollView.h
//  schumacher
//
//  Created by kimberly on 4/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SCBannerScrollView;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@protocol SCBannerScrollViewListener

-(void)scBannerScrollViewUpdated: (SCBannerScrollView *)v;
-(void)scBannerScrollView: (SCBannerScrollView *)v
          scrolledToIndex: (int)i;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface SCBannerScrollViewConfig : NSObject
{
    NSString *positionName;
    NSNumber *maxBanners;
    BOOL randomize;
}

-(id)initWithPositionName: (NSString *)p
               maxBanners: (uint)m
                randomize: (BOOL)r;

-(id)initWithPositionName:(NSString *)p;

@property (readonly) NSString *positionName;
@property (readonly) NSNumber *maxBanners;
@property (readonly) BOOL randomize;
@property (readwrite) BOOL bounces;

@end


@interface SCBannerScrollView : UIView
{
    UIScrollView *scrollView;

    SCBannerScrollViewConfig *config;
    
    int currentIndex;
    id<SCBannerScrollViewListener> listener;
}

@property (retain) SCBannerScrollViewConfig *config;
@property (assign) id<SCBannerScrollViewListener> listener;

-(int)numPages;
-(int)currentIndex;
-(void)reloadData;
- (void)scrollToIndex:(int)i;

@end