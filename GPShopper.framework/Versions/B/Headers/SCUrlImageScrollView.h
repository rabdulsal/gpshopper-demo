//
//  SCUrlImageScrollView.h
//  bebe
//
//  Created by kimberly on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SCUrlImageFetching.h"

@class SCUrlImageFetcher;

@interface SCTaggedUrl : NSObject

-(id)initWithUrl: (NSString *)u
             tag: (NSString *)t;

-(NSString *)url;
-(NSString *)tag;

@end



@class SCTaggedImageView;

@protocol SCTaggedImageViewDelegate < NSObject >
-(void)scTaggedImageViewClicked: (SCTaggedImageView *)t;
@end

@interface SCTaggedImageView : UIView
@property (readonly) UIButton *button;
@property (copy) NSString *imageTag;
@property (assign) id<SCTaggedImageViewDelegate> delegate;
-(IBAction)click:(id)sender;
@end


@interface SCUrlImageScrollInternalItem : NSObject

@property (readonly) NSString *imageTag;
@property (readonly) NSString *url;
@property (retain) UIImage *image;
@property (readwrite) BOOL displayed;

-(id)initWithImageTag: (NSString *)t
                  url: (NSString *)u;

@end


@class SCUrlImageScrollView;
@class SCTaggedObject;

@protocol SCUrlImageScrollViewDelegate < NSObject >

@optional

-(void)scUrlImageScrollView: (SCUrlImageScrollView *)v
        clickedImageWithTag: (NSString *)t;

-(void)scUrlImageScrollView: (SCUrlImageScrollView *)sv
                  loadedUrl: (NSString *)u
                    withTag: (NSString *)t;

@end


@interface SCUrlImageScrollView : UIView <UIScrollViewDelegate,SCUrlImageFetcherListener>
{
    UIScrollView *scrollView;
    NSArray *taggedUrls;
    NSArray *internalItems;
    SCUrlImageFetcher *imageFetcher;
    
    double borderWidth;
    UIColor *selectedBorderColor;
    UIColor *unselectedBorderColor;
    
    int selectedIndex;
    NSString *stagedSelectTag;
    
    id<SCUrlImageScrollViewDelegate> delegate;
    
    BOOL fixedSizeImageEnabled;
    CGFloat fixedImageHeight;
    CGFloat fixedImageWidth;
}

@property (retain) NSArray *taggedUrls;
@property (readonly) int selectedIndex;
@property (assign) id<SCUrlImageScrollViewDelegate> delegate;
@property (assign) BOOL useBackgroundColor;

@property (readonly) IBOutlet UIScrollView *scrollView;

/** @name Scroll indicators */

@property (readonly) IBOutlet UIView *leftIndicatorView;
@property (readonly) IBOutlet UIView *rightIndicatorView;
@property (readwrite) double indicatorOffset;

@property (readonly) IBOutlet UIPageControl *pageControl;

// hide
@property (readwrite) double borderWidth;
@property (retain) UIColor *selectedBorderColor;
@property (retain) UIColor *unselectedBorderColor;

@property (assign) CGFloat tagSpacing;
-(void)fixedSizeImageWidth:(CGFloat)w  Height:(CGFloat)h;

@property (assign) BOOL fixedSizeImageEnabled;
@property (assign) NSUInteger urlImageStorageTargets;

-(void)selectImageWithTag: (NSString *)t;

-(UIButton *)selectedButton;

-(SCTaggedImageView *)newViewForTag: (NSString *)t
                              image: (UIImage *)i
                               size: (CGSize)s;

-(SCTaggedImageView *)existingViewForTag: (NSString *)t;

-(NSArray *)visibleTags;

@end
