//
//  MomentFetcher.h
//
//  Created by Patrick Caraher on 8/28/12.
//  Copyright (c) 2012 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"
#import "Moment.h"

#define kMomentAddedNotification @"MomentAddedNotification"
#define kMomentsFetchedNotification @"MomentsFetchedNotification"

#define kMomentSuccessKey @"success"
#define kMomentMomentsKey @"moments"


#define kMomentErrDomain @"momentErrDomain"
#define kMomentInvalidStatus 1
#define kMomentErrorsKey @"errors"

@interface MomentFetcher : NSObject <SCObjectRetrieverListener>
{
    SCObjectRetriever *addRetriever;
    SCObjectRetriever *fetchRetriever;
@private
    NSString *callbackHost;
}

+ (MomentFetcher *)defaultMomentFetcher;
+ (void)setRequestUrl:(NSString *)requestUrl;

- (void)addMoment:(Moment *)moment error:(NSError **)error;
- (void)fetchMoments;

@end
