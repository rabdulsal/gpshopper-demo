//
//  SCDWProfile.h
//  michaels
//
//  Created by James Lee on 7/19/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

@interface SCDWProfile : NSObject

@property (nonatomic, strong) NSString *first_name;
@property (nonatomic, strong) NSString *last_name;
@property (nonatomic, strong) NSString *birthday;
@property (nonatomic, strong) NSString *gender;
@property (nonatomic, strong) NSString *phone_mobile;
@property (nonatomic, strong) NSString *phone_home;
@property (nonatomic, strong) NSString *customer_no;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *zipCode;

@property (nonatomic, strong) NSDictionary *customAttributes;

- (id)initWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary *)dictionaryObject;

@end
