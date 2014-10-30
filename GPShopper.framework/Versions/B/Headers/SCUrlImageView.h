//
//  SCUrlImageView.h
//  giggle
//
//  Created by kimberly on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SCURLIMAGEVIEW_H
#define SCURLIMAGEVIEW_H

#import <UIKit/UIKit.h>

@class SCUrlImageFetcher;

@interface SCUrlImageView : UIImageView
{
    NSString *url;
    SCUrlImageFetcher *imageFetcher;
    UIActivityIndicatorView *spinner;
    UIColor *delayedBackgroundColor;
}

@property (copy) NSString *url;
@property (retain) UIColor *delayedBackgroundColor;
@property (assign) NSUInteger urlImageStorageTargets;



@end

#endif