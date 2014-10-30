//
//  SCDeviceSession.h
//
//  Created by donny on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"

@interface SCDevId : NSObject {

    uint64_t devid;

}

@property (readonly) uint64_t devid;

-(id)initWithDevid:(uint64_t)d;


@end



extern NSString * const SCDeviceSessionUpdatedNotificationName;

@interface SCDeviceSession : NSObject <SCObjectRetrieverListener>
{
    
    SCObjectRetriever *retriever;
    NSDictionary *responseHeaders;
    id listener;
}

@property (readonly) NSDictionary *responseHeaders;

+(SCDeviceSession *)defaultDeviceSession;
+(void)setRequestUrl: (NSString *)s;
-(void)fetchDeviceSessionForDevid:(NSString *)devid;
-(NSString *)jsessionid;


@end
