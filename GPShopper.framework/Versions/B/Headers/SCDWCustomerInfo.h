//
//  SCDWCustomerInfo.h
//  michaels
//
//  Created by James Lee on 7/23/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

@interface SCDWCustomerInfo : NSObject

@property (strong, nonatomic) NSString *email;

@property (strong, nonatomic) NSDictionary *customAttributes; // client-specific keys

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)dictionaryObject;

@end
