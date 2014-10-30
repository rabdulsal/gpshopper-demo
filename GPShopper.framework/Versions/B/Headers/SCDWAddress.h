//
//  SCDWAddress.h
//
//  Created by James Lee on 7/19/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

@interface SCDWAddress : NSObject

@property (strong, nonatomic) NSString *address1;
@property (strong, nonatomic) NSString *address2;
@property (strong, nonatomic) NSString *city;
@property (strong, nonatomic) NSString *company_name;
@property (strong, nonatomic) NSString *country_code;
@property (strong, nonatomic) NSString *first_name;
@property (strong, nonatomic) NSString *full_name;
@property (strong, nonatomic) NSString *job_title;
@property (strong, nonatomic) NSString *last_name;
@property (strong, nonatomic) NSString *phone;
@property (strong, nonatomic) NSString *post_box;
@property (strong, nonatomic) NSString *postal_code;
@property (strong, nonatomic) NSString *salutation;
@property (strong, nonatomic) NSString *second_name;
@property (strong, nonatomic) NSString *state_code;
@property (strong, nonatomic) NSString *suffix;
@property (strong, nonatomic) NSString *suite;
@property (strong, nonatomic) NSString *title;

@property (strong, nonatomic) NSDictionary *customAttributes; // client-specific keys

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)dictionaryObject;

@end