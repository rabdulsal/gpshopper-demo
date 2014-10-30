//
//  SCDomain.h
//  feature
//
//  Created by kimberly on 9/10/13.
//  Copyright (c) 2013 GPShopper. All rights reserved.
//

#ifndef SCDOMAIN_H
#define SCDOMAIN_H

#import <Foundation/Foundation.h>


/**
 Stores info for displaying values in a particular domain.
 */
@interface SCDomainValue : NSObject

@property (readonly) NSString *name;
@property (readonly) NSString *swatchUrl;
@property (readonly) NSString *colorHex;
@property (readonly) NSDictionary *supplemental;

-(id)initWithName: (NSString *)n
        swatchUrl: (NSString *)s
         colorHex: (NSString *)h
     supplemental: (NSDictionary *)kv;

@end


/**
 Maintains the following consistency constraint: each value has a non-nil name,
 and each value name is unique across all values.
 */
@interface SCDomain : NSObject

@property (readonly) NSString *name;
@property (readonly) NSArray *values;

-(id)initWithName: (NSString *)n
           values: (NSArray *)vs;

-(SCDomainValue *)valueNamed: (NSString *)n;

@end


/**
 Specifies a data model with one or more domains, each of which contains one or more values.
 */
@protocol SCMultiDomain < NSObject >
-(NSArray *)domains;

/**
 The set of values in domain Z such that x in [x0, x1, ... xn]
 and y in [y0, y1, ... ym].
 */
-(NSArray *)valuesInDomain: (NSString *)a
     subjectToDomainValues: (NSDictionary *)d;
@end


SCDomain* scDomainFromMulti(id<SCMultiDomain> md, NSString *n);


@interface SCCartesianMultiDomain : NSObject < SCMultiDomain >

@property (readonly) NSArray *domains;

-(id)initWithDomains: (NSArray *)ds;

@end


@protocol SCMultiDomainSelection < NSObject >

/**
 The mulitdomain against which selections take place.
 */
-(id<SCMultiDomain>)multiDomain;

-(NSArray *)selectedValuesInDomainNamed: (NSString *)n;

-(void)selectValueNamed: (NSString *)v
          inDomainNamed: (NSString *)d;

-(void)unselectValueNamed: (NSString *)v
            inDomainNamed: (NSString *)d;

@end


enum SCMultiDomainInDomainSelectionPolicy
{
    SCMultiDomainInDomainReplaceValues,
    SCMultiDomainInDomainAccumulateValues
};

@interface SCMultiDomainBaseSelection : NSObject < SCMultiDomainSelection >
{
    @protected
    id<SCMultiDomain> multiDomain;
    NSDictionary *selectedValues;
}

@property (readonly) id<SCMultiDomain> multiDomain;
@property (readonly) enum SCMultiDomainInDomainSelectionPolicy inDomainSelectionPolicy;
@property (readonly) NSDictionary *selectedValues;

-(id)initWithMultiDomain: (id<SCMultiDomain>)md
 inDomainSelectionPolicy: (enum SCMultiDomainInDomainSelectionPolicy)p;

-(SCDomain *)domainNamed: (NSString *)n;

-(NSArray *)domainsConstrainingDomainNamed: (NSString *)n;

-(NSDictionary *)selectedValuesInDomains: (NSArray *)ds;

@end

/**
 Manages selection of values in an domain model.
 */
@interface SCMultiDomainOrderedSelection : SCMultiDomainBaseSelection

@end


@interface SCMultiDomainUnorderedSelection : SCMultiDomainBaseSelection

@end

#endif