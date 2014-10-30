//
//  SCBrowse.h
//  schumacher
//
//  Created by kimberly on 6/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "InfoPacket.h"
#import "SCCache.h"


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface SCBrowseNode : NSObject < NSCoding >
{
    NSString *title;
    NSString *searchTerm;
    NSString *imageUrl;
    NSString *bannerPosition;
    NSString *notes;
    NSArray *children;
    SCBrowseNode *parent;
}

@property (readonly) NSString *title;
@property (readonly) NSString *searchTerm;
@property (readonly) NSString *imageUrl;
@property (readonly) NSArray *children;
@property (readonly) SCBrowseNode *parent;
@property (readonly) NSString *notes;

-(id)initWithTitle: (NSString *)t
        searchTerm: (NSString *)s
          imageUrl: (NSString *)u
    bannerPosition: (NSString *)b
             notes: (NSString *)n
          children: (NSArray *)c;
             


-(NSString *)bannerPosition;
-(NSString *)immediateBannerPosition;
-(SCBrowseNode *)firstChildTitled: (NSString *)t;
-(SCBrowseNode *)nthChild: (NSUInteger)i;
-(NSInteger)numChildren;
-(SCBrowseNode *)rootElement;


@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface SCBrowseNodeBuilder : NSObject
{
    NSMutableArray *childBuidlers;
    NSString *title;
    NSString *searchTerm;
    NSString *imageUrl;
    NSString *bannerPosition;
    NSString *notes;
}

@property (copy) NSString *title;
@property (copy) NSString *searchTerm;
@property (copy) NSString *imageUrl;
@property (copy) NSString *bannerPosition;
@property (copy) NSString *notes;

-(void)addChildBuilder: (SCBrowseNodeBuilder *)b;
-(SCBrowseNode *)newNode;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

@class SCBrowse;

@protocol BrowseDelegate
-(void)browse:(SCBrowse *)browse updatedNode:(SCBrowseNode *)node;
@end

// notification: scbrowse_updated
@interface SCBrowse : NSObject
{
    SCBrowseNode *rootNode;
    SCObjectRetriever *retriever;
}

@property (readonly) SCBrowseNode *rootNode;
@property (assign) id<BrowseDelegate> delegate;

-(void)fetch;

-(void)fetchFromSources: (unsigned int)s;

+(SCCache *)cache;

+(SCBrowse *)defaultHierarchy;

+(void)setRequestUrl: (NSString *)s;


/**
 *  Configure the BrowseDelegate.
 */
+(void)configureBrowse:(id <BrowseDelegate>)delegate;

@end


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


@interface SCBrowseResponseParser : SCRemoteResponseParser
{}
@end