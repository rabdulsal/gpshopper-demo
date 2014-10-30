//
//  BazaarVoiceData.h
//  northface
//
//  Created by Alex Mueller on 2/9/12.
//  Copyright (c) 2012 GPShopper. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"

#define kSCProductReviewKeyUsername @"user"
#define kSCProductReviewKeyLocation @"location"
#define kSCProductReviewKeyTitle @"title"
#define kSCProductReviewKeyText @"text"
#define kSCProductReviewKeyRating @"rating"
#define kSCProductReviewKeyDate @"date"

@interface SCProductReview : NSObject

@property (readonly) NSString *username;
@property (readonly) NSString *location;
@property (readonly) NSString *title;
@property (readonly) NSString *text;
@property (readonly) double rating;
@property (readonly) NSDate *date;

-(id)initWithUsername: (NSString *)u
             location: (NSString *)l
                title: (NSString *)t0
                 text: (NSString *)t1
               rating: (double)r
                 date: (NSDate *)d;

+(SCProductReview *)newFromDictionary: (NSDictionary *)d;

@end


#define kSCProductReviewListAvgRatingKey @"avg_rating"
#define kSCProductReviewListNumReviewsKey @"num_reviews"
#define kSCProductReviewListNumRecommendedKey @"num_recommended"
#define kSCProductReviewListReviewsKey @"reviews"

@interface SCProductReviewList : NSObject

@property (readonly) double avgRating;
@property (readonly) NSUInteger numReviews;
@property (readonly) NSUInteger numRecommended;
@property (readonly) NSArray *reviews;

-(id)initWithAvgRating: (double)a
            numReviews: (NSUInteger)n0
        numRecommended: (NSUInteger)n1
               reviews: (NSArray *)rs;

+(SCProductReviewList *)newFromDictionary: (NSDictionary *)d;

@end


@class SCProductReviewFetcher;

@protocol SCProductReviewFetcherListener < NSObject >

@optional

-(void)scProductReviewFetcher: (SCProductReviewFetcher *)f
     fetchedProductReviewList: (SCProductReviewList *)l
                 forProductId: (NSString *)p;

-(void)scProductReviewFetcher: (SCProductReviewFetcher *)f
       failedToFetchWithError: (NSError *)e
                 forProductId: (NSString *)p;

@end


@interface SCProductReviewFetcher : NSObject < SCObjectRetrieverListener >
{
    BOOL fetchInProgress;
	SCObjectRetriever *retriever;
}

@property (assign) id<SCProductReviewFetcherListener> listener;

+(void)setRequestUrl: (NSString *)u;
+(void)setLimit:(NSUInteger)l;

-(void)fetchReviewsForProductId: (NSString *)p;

@end
