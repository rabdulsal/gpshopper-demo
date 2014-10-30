//
//  SCEnrypt.h
//  schumacher
//
//  Created by Patrick Caraher on 7/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"


@interface SCEncrypt : NSObject
{
    NSString *keyUrlString;
    NSData *certificateData;    
    BOOL keyIsNew;
}

@property (nonatomic, copy) NSString *keyUrlString;
@property (readonly) BOOL keyIsNew;
@property (readonly) enum SCRemoteStatus remoteStatus;

-(BOOL)keyIsNew;
-(void)fetch;
-(void)acknowledgeNewKey;
-(NSString *)encryptString: (NSString *)s;
-(NSString *)decryptData:(NSData *)d;

+(SCEncrypt *)defaultEncrypt;


@end
