//
//  SCDWRetriever.h
//
//  Created by James Lee on 7/30/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^SCDWResponseBlock)(id object, NSError *error);

@interface SCDWRetriever : NSObject

@property (copy, nonatomic) SCDWResponseBlock completionBlock;
@property (strong, nonatomic) NSString *requestMethod;
@property (strong, nonatomic) NSDictionary *args;

+(NSString *)requestUrl;
+(void)setRequestUrl: (NSString *)url;

+ (void)sendRequestForMethod:(NSString *)method args:(NSDictionary *)args completion:(SCDWResponseBlock)completion;
+ (NSObject *)sendSynchronousRequestForMethod:(NSString *)method args:(NSDictionary *)args error:(NSError **)error;

@end


// Special case errors for demandware fetches
typedef enum : NSUInteger {
    kSCDWUnauthorizedConnection = -1000,
    kSCDWDemandwareError        = -1001,
    kSCDWUnknownError           = -1002
} SCDWErrorType;


